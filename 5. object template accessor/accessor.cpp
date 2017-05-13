#include <node.h>

namespace __accessor__ {

using v8::External;
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
using v8::Persistent;
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

class TestExternal {
public:
    TestExternal(Local<Object> obj)
    {
        value = 233;
        _handle.Reset(Isolate::GetCurrent(), obj);
        _handle.SetWeak(this, WeakCallback, v8::WeakCallbackType::kParameter);
        _handle.MarkIndependent();
    }

    ~TestExternal()
    {
    }

    void Set(int _value)
    {
        value = _value;
    }

    int Get()
    {
        return value;
    }

    Persistent<Object> _handle;

    static void WeakCallback(const v8::WeakCallbackInfo<TestExternal>& data)
    {
        TestExternal* ex = data.GetParameter();
        ex->_handle.Reset();
        delete ex;
    }

private:
    int value;
};

void Getter3(Local<String> property, const PropertyCallbackInfo<Value>& info)
{
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    TestExternal* ex = (TestExternal*)ptr;

    info.GetReturnValue().Set(ex->Get());
}

void Setter3(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info)
{
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    TestExternal* ex = (TestExternal*)ptr;

    ex->Set(value->ToInt32()->Value());
}

void Init(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    // 全局变量
    Local<ObjectTemplate> tpl = ObjectTemplate::New(isolate);
    tpl->SetInternalFieldCount(1);
    tpl->SetAccessor(String::NewFromUtf8(isolate, "var1"), Getter1, Setter1);

    // 类全局变量
    Local<Object> inner = Object::New(isolate);
    inner->Set(String::NewFromUtf8(isolate, "inner"), String::NewFromUtf8(isolate, "蛋花汤"));
    tpl->SetAccessor(String::NewFromUtf8(isolate, "var2"), Getter2, Setter2, inner);

    // 动态变量
    tpl->SetAccessor(String::NewFromUtf8(isolate, "var3"), Getter3, Setter3);

    Local<Object> ret = tpl->NewInstance();
    TestExternal* ex = new TestExternal(ret);
    ret->SetInternalField(0, External::New(isolate, ex));

    module->Set(String::NewFromUtf8(isolate, "exports"), ret);
}

NODE_MODULE(accessor, Init)

}
