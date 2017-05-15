#include <node.h>

namespace __template__ {

using v8::FunctionCallbackInfo;
using v8::HandleScope;
using v8::ObjectTemplate;
using v8::FunctionTemplate;
using v8::Function;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Array;

void Constructor(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    args.This()->Set(String::NewFromUtf8(isolate, "value"), Number::New(isolate, 233));
    return args.GetReturnValue().Set(args.This());
}

void ClassGet(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    return args.GetReturnValue().Set(args.This()->Get(String::NewFromUtf8(isolate, "value")));
}

void Func(const FunctionCallbackInfo<Value>& args)
{
    args.GetReturnValue().Set(2333);
}

void Init(Local<Object> exports)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // 作为函数模板的原型
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, Constructor);
    tpl->SetClassName(String::NewFromUtf8(isolate, "TestClass"));
    Local<ObjectTemplate> proto = tpl->PrototypeTemplate();
    proto->Set(String::NewFromUtf8(isolate, "get"), FunctionTemplate::New(isolate, ClassGet));

    exports->Set(String::NewFromUtf8(isolate, "TestClass"), tpl->GetFunction());

    // 作为对象模板创建对象
    Local<FunctionTemplate> fun = FunctionTemplate::New(isolate);
    fun->SetClassName(String::NewFromUtf8(isolate, "TestClass2"));
    Local<ObjectTemplate> obj_tpl = ObjectTemplate::New(isolate, fun);
    obj_tpl->Set(String::NewFromUtf8(isolate, "num"), Number::New(isolate, 233));
    Local<Array> array = Array::New(isolate, 10);
    for(int i = 0; i < 10; i++)
    {
        array->Set(Number::New(isolate, i), obj_tpl->NewInstance());
    }
    exports->Set(String::NewFromUtf8(isolate, "array"), array);

    // 设置函数体
    Local<ObjectTemplate> obj_with_func_tpl = ObjectTemplate::New(isolate);
    obj_with_func_tpl->Set(String::NewFromUtf8(isolate, "cat"),
            String::NewFromUtf8(isolate, "南瓜饼"));
    obj_with_func_tpl->Set(String::NewFromUtf8(isolate, "dog"),
            String::NewFromUtf8(isolate, "蛋花汤"));
    obj_with_func_tpl->SetCallAsFunctionHandler(Func);
    exports->Set(String::NewFromUtf8(isolate, "func"), obj_with_func_tpl->NewInstance());
}

NODE_MODULE(_template, Init)

}
