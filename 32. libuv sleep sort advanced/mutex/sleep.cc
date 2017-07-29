#include <nan.h>
#include <vector>

namespace __sleep__ {

using v8::Array;
using v8::Local;
using v8::Value;

#ifdef WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

struct ScopeLock {
    uv_mutex_t* handle;

    ScopeLock(uv_mutex_t* handle) : handle(handle)
    {
        uv_mutex_lock(handle);
    }
    
    ~ScopeLock()
    {
        uv_mutex_unlock(handle);
    }
};

void _Sleep(int sleep_ms)
{
#ifdef WINDOWS
    Sleep(sleep_ms);
#else
    usleep(sleep_ms * 1000);
#endif
}

struct ThreadArg {
    std::vector<uint32_t>* vec;
    uint32_t num;
    uv_mutex_t* mutex_handle;
};

void Sleep(void* _)
{
    ThreadArg* arg = (ThreadArg*)_;

    // 睡上 num * 100 毫秒
    _Sleep(arg->num * 100);

    ScopeLock lock(arg->mutex_handle);
    arg->vec->push_back(arg->num);

    delete arg;
}

NAN_METHOD(Sort)
{
    if(info.Length() < 1 || !info[0]->IsArray())
    {
        return Nan::ThrowError("Wrong argument");
    }
 
    Local<Array> array = info[0].As<Array>();
    if(!array->Length())
    {
        return info.GetReturnValue().Set(Nan::New<Array>());
    }

    std::vector<uint32_t> orig;
    for(uint32_t i = 0; i < array->Length(); i++)
    {
        if(!Nan::Get(array, i).ToLocalChecked()->IsUint32())
        {
            return Nan::ThrowTypeError("Elements should be unsigned int.");
        }

        orig.push_back(Nan::To<uint32_t>(Nan::Get(array, i).ToLocalChecked()).FromJust());
    }

    std::vector<uint32_t> vec;
    std::vector<uv_thread_t> handles(array->Length());
    uv_mutex_t handle;
    uv_mutex_init(&handle);
    for(uint32_t i = 0; i < array->Length(); i++)
    {
        ThreadArg* arg = new ThreadArg();
        arg->vec = &vec;
        arg->num = orig[i];
        arg->mutex_handle = &handle;
        uv_thread_create(&handles[i], Sleep, arg);
    }

    for(uint32_t i = 0; i < handles.size(); i++)
    {
        uv_thread_join(&handles[i]);
    }

    uv_mutex_destroy(&handle);
    Local<Array> ret = Nan::New<Array>();
    for(uint32_t i = 0; i < array->Length(); i++)
    {
        Local<Value> v = Nan::New(vec[i]);
        Nan::Set(ret, i, v);
    }

    info.GetReturnValue().Set(ret);
}

NAN_MODULE_INIT(Init)
{
    Nan::Export(target, "sort", Sort);
}

NODE_MODULE(mutex_sleep, Init)

}
