#include <node.h>

namespace __entry__ {

using v8::FunctionCallbackInfo;
using v8::Function;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::HandleScope;

void RunCallback(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<Function> cb = Local<Function>::Cast(args[0]);
    const unsigned argc = 1;
    Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world") };
    cb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}

void init(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    NODE_SET_METHOD(exports, "runCallback", RunCallback);

    Local<Object> global = isolate->GetCurrentContext()->Global();
    Local<Object> console = global->Get(String::NewFromUtf8(isolate, "console"))->ToObject();
    Local<Function> log = Local<Function>::Cast(console->Get(String::NewFromUtf8(isolate, "log")));
    Local<Value> argv[3] = { module, String::NewFromUtf8(isolate, "---"), exports };

    log->Call(console, 3, argv);
}

NODE_MODULE(addon, init)

}