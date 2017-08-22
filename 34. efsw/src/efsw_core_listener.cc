/**
 * node-efsw - Node.js binding for EFSW
 *
 * Copyright (c) 2017 XadillaX <i@2333.moe>
 *
 * MIT License <https://github.com/XadillaX/node-efsw/blob/master/LICENSE>
 */
#include "efsw_core_listener.h"
using namespace std;
using namespace efsw;
using namespace v8;

namespace efsw_core {

struct AsyncArgs {
    string dir;
    string filename;
    string old_filename;
    Action action;
    Nan::Callback* callback;

    uv_async_t handle;
};

void OnAsyncClosed(uv_handle_t* handle)
{
    uv_async_t* async = (uv_async_t*)handle;
    AsyncArgs* data = (AsyncArgs*)async->data;
    delete data;
}

void OnEFSWEvent(uv_async_t* handle)
{
    Nan::HandleScope scope;
    AsyncArgs* data = (AsyncArgs*)handle->data;
    Local<Value> argv[] = {
        Nan::New(data->dir.c_str()).ToLocalChecked(),
        Nan::New(data->filename.c_str()).ToLocalChecked(),
        Nan::New(data->old_filename.c_str()).ToLocalChecked(),
        Nan::New(data->action)
    };
    data->callback->Call(4, argv);
    uv_close((uv_handle_t*)handle, OnAsyncClosed);
}

EFSWCoreListener::EFSWCoreListener(Nan::Callback* listener) :
    listener(listener)
{
}

EFSWCoreListener::~EFSWCoreListener()
{
}

void EFSWCoreListener::HandleFileAction(
        efsw::WatchId,
        const std::string& dir,
        const std::string& filename,
        efsw::Action action,
        std::string old_filename)
{
    AsyncArgs* args = new AsyncArgs();
    args->dir = dir;
    args->filename = filename;
    args->old_filename = old_filename;
    args->action = action;
    args->callback = listener;

    uv_async_init(uv_default_loop(), &args->handle, OnEFSWEvent);
    args->handle.data = (void*)args;
    uv_async_send(&args->handle);
}

}
