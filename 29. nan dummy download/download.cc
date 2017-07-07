#include <nan.h>
#include <string>
#include "../deps/minihttp/minihttp.h"

namespace __download__ {

using v8::Function;
using v8::Local;
using v8::String;
using v8::Value;
using Nan::AsyncProgressWorker;
using namespace std;

class HttpDumpSocket : public minihttp::HttpSocket {
public:
    HttpDumpSocket(const AsyncProgressWorker::ExecutionProgress& progress) :
        progress(&progress)
    {
    }
    virtual ~HttpDumpSocket() {}

protected:
    void _OnRecv(void* buf, unsigned int size)
    {
        if(!size) return;
        progress->Send((const char*)buf, size);
    }

private:
    const AsyncProgressWorker::ExecutionProgress* progress;
};

class DownloadWorker : public AsyncProgressWorker {
public:
    DownloadWorker(string uri, Nan::Callback* callback, Nan::Callback* processor) :
        AsyncProgressWorker(callback),
        processor(processor),
        uri(uri)
    {
    }

    ~DownloadWorker()
    {
        delete processor;
    }

    void Execute(const AsyncProgressWorker::ExecutionProgress& progress)
    {
        HttpDumpSocket ht(progress);
        ht.SetBufsizeIn(64 * 1024);
        ht.SetFollowRedirect(true);
        ht.SetUserAgent("minihttp");
        ht.SetNonBlocking(false);
        ht.SetAlwaysHandle(false);
        ht.Download(uri);
        while(ht.isOpen() || ht.HasPendingTask()) ht.update();
    }

    void HandleProgressCallback(const char* data, size_t count)
    {
        Nan::HandleScope scope;

        Local<Value> argv[] = {
            Nan::CopyBuffer(data, count).ToLocalChecked()
        };
        processor->Call(1, argv);
    }

private:
    Nan::Callback* processor;
    string uri;
};

NAN_METHOD(Download)
{
    Local<String> uri = Nan::To<String>(info[0]).ToLocalChecked();
    Nan::Utf8String curi(uri);

    Nan::Callback* processor = new Nan::Callback(info[1].As<Function>());
    Nan::Callback* callback = new Nan::Callback(info[2].As<Function>());

    Nan::AsyncQueueWorker(new DownloadWorker(*curi, callback, processor));
}

static void AtExit(void* arg)
{
    minihttp::StopNetwork();
}

NAN_MODULE_INIT(Init)
{
    minihttp::InitNetwork();
    node::AtExit(AtExit);

    Nan::Export(target, "download", Download);
}

NODE_MODULE(reverse, Init)

}
