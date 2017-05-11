#include <node.h>

namespace __accessor__ {

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
using v8::PropertyCallbackInfo;

int x = 0;

void Getter1(Local<String> property, const PropertyCallbackInfo<Value>& info)
{
    info.GetReturnValue().Set(x);
}

void Setter1(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info)
{
    x = value->Int32Value();
}

void Getter2(Local<String> property, const PropertyCallbackInfo<Value>& info)
{
    info.GetReturnValue().Set(info.Data()->ToObject()->Get(String::NewFromUtf8(info.GetIsolate(), "inner")));
}

void Setter2(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info)
{
    info.Data()->ToObject()->Set(String::NewFromUtf8(info.GetIsolate(), "inner"), value);
}

void Init(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<ObjectTemplate> tpl = ObjectTemplate::New(isolate);
    tpl->SetAccessor(String::NewFromUtf8(isolate, "var1"), Getter1, Setter1);

    Local<Object> inner = Object::New(isolate);
    inner->Set(String::NewFromUtf8(isolate, "inner"), String::NewFromUtf8(isolate, "蛋花汤"));
    tpl->SetAccessor(String::NewFromUtf8(isolate, "var2"), Getter2, Setter2, inner);

    module->Set(String::NewFromUtf8(isolate, "exports"), tpl->NewInstance());
}

NODE_MODULE(accessor, Init)

}
