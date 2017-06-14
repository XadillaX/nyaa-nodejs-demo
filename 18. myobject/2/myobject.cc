#include "myobject.h"

namespace __addon2__ {

using v8::Isolate;
using v8::FunctionTemplate;
using v8::String;
using v8::Number;
using v8::Context;

Persistent<Function> MyObject::constructor;

MyObject::MyObject(double value) : value_(value)
{
}

MyObject::~MyObject()
{
}

void MyObject::Init(Local<Object> exports)
{
    Isolate* isolate = exports->GetIsolate();
    
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", PlusOne);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "MyObject"), tpl->GetFunction());
}

void MyObject::New(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    if(args.IsConstructCall()) {
        // 如果是 `new` 构造函数调用，则逻辑不变
        double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        MyObject* obj = new MyObject(value);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else {
        // 如果不是 `new` 构造函数调用，则通过持久化构造函数句柄生成
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        Local<Context> context = isolate->GetCurrentContext();
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        Local<Object> result =
                cons->NewInstance(context, argc, argv).ToLocalChecked();
        args.GetReturnValue().Set(result);
    }
}

void MyObject::PlusOne(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
    obj->value_ += 1;

    args.GetReturnValue().Set(Number::New(isolate, obj->value_));
}

}
