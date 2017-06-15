#include <nan.h>

namespace __map__ {

using Nan::FunctionCallbackInfo;
using v8::Local;
using v8::Array;
using v8::Int32;
using v8::Function;
using v8::Object;
using v8::Value;

void Map(const FunctionCallbackInfo<Value>& args)
{
    Local<Array> array = args[0].As<Array>();
    Local<Function> func = args[1].As<Function>();

    Local<Array> ret = Nan::New<Array>(array->Length());

    Local<Value> null = Nan::Null();
    Local<Value> a[3] = { Nan::New<Object>(), null, array };
    for(uint32_t i = 0; i < array->Length(); i++)
    {
        a[0] = array->Get(i);
        a[1] = Nan::New<Int32>(i);

        Local<Value> v = Nan::MakeCallback(args.This(), func, 3, a);
        ret->Set(i, v);
    }

    args.GetReturnValue().Set(ret);
}

NAN_MODULE_INIT(Init)
{
    Nan::Export(target, "map", Map);
}

NODE_MODULE(map, Init)

}
