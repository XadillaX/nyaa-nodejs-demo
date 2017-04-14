#include <node.h>

namespace __first__ {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "first build"));
}

void init(Local<Object> exports)
{
    NODE_SET_METHOD(exports, "first", Method);
}

NODE_MODULE(addon, init)

}