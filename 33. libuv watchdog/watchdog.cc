#include <nan.h>
#include <map>
#include "../deps/efsw/include/efsw/efsw.hpp"

namespace __watchdog__ {

using v8::Array;
using v8::Local;
using v8::Value;

#define Watch watch
#define AddWatch addWatch
#define HandleFileAction handleFileAction
#define GetLastErrorLog getLastErrorLog

efsw::FileWatcher* file_watcher;

struct AsyncArgs {
    efsw::WatchID watch_id;
    std::string dir;
    std::string filename;
    efsw::Action action;
    std::string old_filename;
    uv_async_t handle;
    Nan::Callback* callback;
};

void OnAsyncClosed(uv_handle_t* handle)
{
    uv_async_t* async = (uv_async_t*)handle;
    AsyncArgs* data = (AsyncArgs*)async->data;
    delete data;
}

void OnEvent(uv_async_t* handle)
{
    Nan::HandleScope scope;
    AsyncArgs* data = (AsyncArgs*)handle->data;
    Local<Value> argv[] = {
        Nan::New((int)data->watch_id),
        Nan::New(data->dir.c_str()).ToLocalChecked(),
        Nan::New(data->filename.c_str()).ToLocalChecked(),
        Nan::New(data->action),
        Nan::New(data->old_filename.c_str()).ToLocalChecked()
    };
    data->callback->Call(5, argv);
    uv_close((uv_handle_t*)handle, OnAsyncClosed);
}

class UpdateListener : public efsw::FileWatchListener {
public:
    UpdateListener(Nan::Callback* callback) :
        callback(callback)
    {
    }

    ~UpdateListener()
    {
        Nan::HandleScope scope;
        delete callback;
    }

    void HandleFileAction(
            efsw::WatchID watchid,
            const std::string& dir,
            const std::string& filename,
            efsw::Action action,
            std::string old_filename)
    {
        AsyncArgs* args = new AsyncArgs();
        args->watch_id = watchid;
        args->dir = dir;
        args->filename = filename;
        args->action = action;
        args->old_filename = old_filename;
        args->callback = callback;
        uv_async_init(uv_default_loop(), &args->handle, OnEvent);
        args->handle.data = (void*)args;
        uv_async_send(&args->handle);
    }

private:
    Nan::Callback* callback;
};

std::map<std::string, std::vector<UpdateListener*> > listeners;

NAN_METHOD(Watch)
{
    if(info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
    {
        return Nan::ThrowError("Wrong argument");
    }

    Nan::Utf8String path(info[0]->ToString());
    Nan::Callback* callback = new Nan::Callback(info[1].As<v8::Function>());

    // 半成品，没有地方回收该指针
    UpdateListener* listener = new UpdateListener(callback);
    listeners[*path].push_back(listener);

    efsw::WatchID watch_id = file_watcher->AddWatch(*path, listener, true);

    if(watch_id < 0)
    {
        return Nan::ThrowError(efsw::Errors::Log::GetLastErrorLog().c_str());
    }

    info.GetReturnValue().Set(Nan::New((int)watch_id));
}

NAN_MODULE_INIT(Init)
{
    // 半成品，没有地方回收该指针
    file_watcher = new efsw::FileWatcher();
    file_watcher->Watch();

    Nan::Export(target, "watch", Watch);
}

NODE_MODULE(watchdog, Init)

}
