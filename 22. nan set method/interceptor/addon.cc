#include <nan.h>
#include <util.h>
#include "../../deps/minihttp/minihttp.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace __interceptor__ {

using v8::Array;
using v8::Number;
using v8::Object;
using v8::ObjectTemplate;
using v8::String;
using v8::Value;
using v8::Local;

Local<Array> GetList()
{
    Nan::EscapableHandleScope scope;
    Nan::JSON json;

    char* content = minihttp::Download("https://cnodejs.org/api/v1/topics");
    Local<Value> ret = json.Parse(Nan::New(content).ToLocalChecked()).ToLocalChecked();
    free(content);

    Local<Array> data = Nan::Get(ret->ToObject(), Nan::New("data").ToLocalChecked())
            .ToLocalChecked().As<Array>();

    printf("fetching %s for %s...ok\n", "https://cnodejs.org/api/v1/topics", "list");

    return scope.Escape(data);
}

Local<Object> GetTopic(const char* id, const char* usage)
{
    Nan::EscapableHandleScope scope;
    Nan::JSON json;

    int url_length = strlen("https://cnodejs.org/api/v1/topic/") + strlen(id);
    char url[url_length + 1];
    url[0] = 0;
    strcat(url, "https://cnodejs.org/api/v1/topic/");
    strcat(url, id);

    printf("fetching %s for %s...", url, usage);

    char* content = minihttp::Download(url);
    if(0 == content)
    {
        printf("failed\n");
        return Local<Object>();
    }

    Local<Value> ret = json.Parse(Nan::New(content).ToLocalChecked()).ToLocalChecked();
    free(content);

    if(Nan::Get(ret->ToObject(), Nan::New("success").ToLocalChecked())
            .ToLocalChecked()->IsFalse()) {
        printf("failed\n");
        return Local<Object>();
    }

    Local<Object> data = Nan::Get(ret->ToObject(), Nan::New("data").ToLocalChecked())
            .ToLocalChecked()->ToObject();

    printf("ok\n");
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

NAN_PROPERTY_GETTER(Getter)
{
    if(!property->IsString()) return;

    Nan::Utf8String key(property);

    Local<Object> data = GetTopic(*key, "getter");
    __Sleep();
    
    if(!data.IsEmpty())
    {
        info.GetReturnValue().Set(Nan::Get(data, Nan::New("title").ToLocalChecked())
                .ToLocalChecked()->ToString());
    }
}

NAN_PROPERTY_QUERY(Query)
{
    if(!property->IsString()) return;

    Nan::Utf8String key(property);

    Local<Object> data = GetTopic(*key, "query");
    __Sleep();

    if(!data.IsEmpty())
    {
        info.GetReturnValue().Set(
            static_cast<int32_t>(v8::ReadOnly) |
            static_cast<int32_t>(v8::DontEnum));
        return;
    }
}

NAN_PROPERTY_ENUMERATOR(Enumerator)
{
    Local<Array> data = GetList();
    __Sleep();

    for(unsigned int i = 0; i < data->Length(); i++)
    {
        Local<Object> element = Nan::Get(data, Nan::New(i)).ToLocalChecked()->ToObject();
        Local<String> id = Nan::Get(element, Nan::New("id").ToLocalChecked())
                .ToLocalChecked()->ToString();
        Nan::Set(data, Nan::New(i), id);
    }

    info.GetReturnValue().Set(data);
}

NAN_MODULE_INIT(Init)
{
    minihttp::InitNetwork();
    atexit(minihttp::StopNetwork);

    Local<ObjectTemplate> tpl = Nan::New<ObjectTemplate>();
    Nan::SetNamedPropertyHandler(tpl, Getter, 0, Query, 0, Enumerator);
    Nan::Set(target, Nan::New("cnode").ToLocalChecked(), tpl->NewInstance());
}

NODE_MODULE(interceptor, Init)

}
