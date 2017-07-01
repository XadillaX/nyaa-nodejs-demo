#include <nan.h>

namespace __buffer__ {

using v8::Local;
using v8::Object;

void FreeCallback(char* buf, void* hint)
{
    printf("Free.\n");
    delete []buf;
    printf("Freed.\n");
}

NAN_METHOD(PlusOne1)
{
    Local<Object> old = Nan::To<Object>(info[0]).ToLocalChecked();

    unsigned int length = node::Buffer::Length(old);
    char* buf = node::Buffer::Data(old);

    for(unsigned int i = 0; i < length; i++)
    {
        buf[i] ^= 233;
    }

    info.GetReturnValue().Set(Nan::NewBuffer(
                buf,
                length,
                FreeCallback,
                0).ToLocalChecked());
}

NAN_METHOD(PlusOne2)
{
    Local<Object> old = Nan::To<Object>(info[0]).ToLocalChecked();

    unsigned int length = node::Buffer::Length(old);
    char* buf = node::Buffer::Data(old);

    for(unsigned int i = 0; i < length; i++)
    {
        buf[i] ^= 233;
    }

    info.GetReturnValue().Set(Nan::CopyBuffer(buf, length).ToLocalChecked());
}

NAN_METHOD(PlusOne3)
{
    Local<Object> old = Nan::To<Object>(info[0]).ToLocalChecked();

    unsigned int length = node::Buffer::Length(old);
    char* buf = new char[length];
    memcpy(buf, node::Buffer::Data(old), length);
    for(unsigned int i = 0; i < length; i++)
    {
        buf[i] ^= 233;
    }

    info.GetReturnValue().Set(Nan::NewBuffer(
                buf,
                length,
                FreeCallback,
                0).ToLocalChecked());
}

NAN_MODULE_INIT(Init)
{
    Nan::Export(target, "plusOne1", PlusOne1);
    Nan::Export(target, "plusOne2", PlusOne2);
    Nan::Export(target, "plusOne3", PlusOne3);
}

NODE_MODULE(reverse, Init)

}
