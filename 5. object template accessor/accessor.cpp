#include <node.h>

namespace __accessor__ {

using v8::Context;
using v8::External;
using v8::FunctionCallbackInfo;
using v8::HandleScope;
using v8::ObjectTemplate;
using v8::FunctionTemplate;
using v8::Function;
using v8::Isolate;
using v8::Local;
using v8::MaybeLocal;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Array;
using v8::Persistent;
using v8::PropertyCallbackInfo;

int x = 0;

// Mentioned @ https://github.com/XadillaX/nyaa-nodejs-demo/issues/2
#define CURRENT_CONTEXT(ctx) Isolate* isolate = Isolate::GetCurrent(); \
                                Local<Context> ctx = isolate->GetCurrentContext();

void Getter1(Local<String> property, const PropertyCallbackInfo<Value>& info)
{
    info.GetReturnValue().Set(x);
}

void Setter1(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info)
{
#if NODE_MODULE_VERSION >= 67 // Node.js 11.0.0+
    CURRENT_CONTEXT(context);
    x = value->Int32Value(context).FromJust();
#else
    x = value->Int32Value();
#endif
}

void Getter2(Local<String> property, const PropertyCallbackInfo<Value>& info)
{
#if NODE_MODULE_VERSION >= 67 // Node.js 11.0.0+
    CURRENT_CONTEXT(context);
    info.GetReturnValue().Set(
            info.Data()->ToObject(context).ToLocalChecked()->Get(String::NewFromUtf8(info.GetIsolate(), "inner")));
#else
    info.GetReturnValue().Set(info.Data()->ToObject()->Get(String::NewFromUtf8(info.GetIsolate(), "inner")));
#endif
}

void Setter2(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info)
{
#if NODE_MODULE_VERSION >= 67
    CURRENT_CONTEXT(context);
    info.Data()->ToObject(context).ToLocalChecked()->Set(String::NewFromUtf8(info.GetIsolate(), "inner"), value);
#else
    info.Data()->ToObject()->Set(String::NewFromUtf8(info.GetIsolate(), "inner"), value);
#endif
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
#if NODE_MODULE_VERSION >= 67 // Node.js 11.0.0+
    CURRENT_CONTEXT(context);
#endif

    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    TestExternal* ex = (TestExternal*)ptr;

#if NODE_MODULE_VERSION >= 67 // Node.js 11.0.0+
    ex->Set(value->ToInt32(context).ToLocalChecked()->Value());
#else
    ex->Set(value->ToInt32()->Value());
#endif
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

    Local<Object> ret = ((MaybeLocal<Object>)tpl->NewInstance()).ToLocalChecked();
    TestExternal* ex = new TestExternal(ret);
    ret->SetInternalField(0, External::New(isolate, ex));

    module->Set(String::NewFromUtf8(isolate, "exports"), ret);
}

NODE_MODULE(accessor, Init)

}
