#include <nan.h>
#include <string>

namespace __array__ {

using v8::Local;
using v8::Array;
using v8::String;

NAN_METHOD(Reverse)
{
    Local<Array> input = Local<Array>::Cast(info[0]);
    Local<Array> output = Nan::New<Array>();

    for(unsigned int i = 0, j = input->Length() - 1; i < input->Length(); i++, j--)
    {
        Nan::Set(output, j, Nan::Get(input, i).ToLocalChecked());
    }

    info.GetReturnValue().Set(output);
}

NAN_MODULE_INIT(Init)
{
    Nan::Export(target, "reverse", Reverse);
}

NODE_MODULE(reverse, Init)

}
