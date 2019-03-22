#include <node.h>
#include "../deps/minihttp/minihttp.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace __interceptor__ {

using v8::FunctionCallbackInfo;
using v8::HandleScope;
using v8::EscapableHandleScope;
using v8::ObjectTemplate;
using v8::FunctionTemplate;
using v8::Function;
using v8::Isolate;
using v8::Local;
using v8::Integer;
using v8::MaybeLocal;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Array;
using v8::Persistent;
using v8::PropertyCallbackInfo;
using v8::Name;
using v8::PropertyHandlerFlags;

Local<Array> GetList(Isolate* isolate)
{
    EscapableHandleScope scope(isolate);

    // 访问 CNode.js API
    char* content = minihttp::Download("https://cnodejs.org/api/v1/topics");
    MaybeLocal<Value> maybe = v8::JSON::Parse(isolate, String::NewFromUtf8(isolate, content));
    Local<Value> ret = maybe.ToLocalChecked();
    free(content);

    // 得到 `data` 数组
    Local<Array> data = Local<Array>::Cast(ret->ToObject()->Get(String::NewFromUtf8(isolate, "data"))->ToObject());

    printf("fetching %s for %s...ok\n", "https://cnodejs.org/api/v1/topics", "list");

    return scope.Escape(data);
}

void __Sleep()
{
#ifdef _WIN32
    Sleep(10);
#else
    usleep(10);
#endif
}

void Getter(uint32_t index, const PropertyCallbackInfo<Value>& info)
{
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);

    Local<Array> data = GetList(isolate);
    __Sleep();
    
    if(!data.IsEmpty() && index < data->Length())
    {
        info.GetReturnValue().Set(
                data->Get(Number::New(isolate, index))->ToObject()->Get(String::NewFromUtf8(isolate, "title")));
    }
}

void Query(uint32_t index, const PropertyCallbackInfo<Integer>& info)
{
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);

    Local<Array> data = GetList(isolate);
    __Sleep();

    if(!data.IsEmpty() && index < data->Length())
    {
        info.GetReturnValue().Set(
            static_cast<int32_t>(v8::ReadOnly) |
            static_cast<int32_t>(v8::DontEnum));
        return;
    }
}

void Enumerator(const PropertyCallbackInfo<Array>& info)
{
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);

    Local<Array> data = GetList(isolate);
    __Sleep();

    for(unsigned int i = 0; i < data->Length(); i++)
    {
        data->Set(Number::New(isolate, i), Number::New(isolate, i));
    }

    info.GetReturnValue().Set(data);
}

void Init(Local<Object> exports, Local<Object> module)
{
    minihttp::InitNetwork();
    atexit(minihttp::StopNetwork);

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<ObjectTemplate> tpl = ObjectTemplate::New(isolate);
    tpl->SetHandler(v8::IndexedPropertyHandlerConfiguration(
            Getter,
            0,
            Query,
            0,
            Enumerator,
            Local<Value>(),
            PropertyHandlerFlags::kNone));

    module->Set(
            String::NewFromUtf8(isolate, "exports"),
            ((v8::MaybeLocal<Object>)tpl->NewInstance()).ToLocalChecked());
}

NODE_MODULE(indexed_property_interceptor, Init)

}
