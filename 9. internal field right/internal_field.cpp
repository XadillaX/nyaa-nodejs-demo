#include <node.h>

namespace __internal_field_right__ {

using v8::FunctionCallbackInfo;
using v8::HandleScope;
using v8::ObjectTemplate;
using v8::FunctionTemplate;
using v8::Function;
using v8::Isolate;
using v8::Local;
using v8::Persistent;
using v8::External;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Array;
using v8::MaybeLocal;

struct PersistentWrapper {
    Persistent<Object> persistent;
    int value;
};

void WeakCallback(const v8::WeakCallbackInfo<PersistentWrapper>& data)
{
    PersistentWrapper* wrapper = data.GetParameter();

    if(!wrapper->persistent.IsNearDeath())
    {
        printf("WARN...\n");
    }

    printf("deleting 0x%.8X: %d...", wrapper, wrapper->value); // NOLINT
    wrapper->persistent.Reset();
    delete wrapper;
    printf("ok\n");
}

void CreateObject(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // 新建对象模板
    Local<ObjectTemplate> templ = ObjectTemplate::New(isolate);
    templ->SetInternalFieldCount(1);

    // 新建对象以及设置内置字段
    PersistentWrapper* wrapper = new PersistentWrapper();
    wrapper->value = args[0]->ToNumber()->Int32Value();
    Local<Object> obj = templ->NewInstance();
    obj->SetInternalField(0, External::New(isolate, wrapper));

    // 基于 obj 新建持久句柄
    wrapper->persistent.Reset(isolate, obj);

    // 将持久句柄设置为弱持久句柄
    wrapper->persistent.SetWeak(wrapper, WeakCallback, v8::WeakCallbackType::kInternalFields);
    wrapper->persistent.MarkIndependent();

    args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    exports->Set(String::NewFromUtf8(isolate, "create"), FunctionTemplate::New(isolate, CreateObject)->GetFunction());
}

NODE_MODULE(_template, Init)

}
