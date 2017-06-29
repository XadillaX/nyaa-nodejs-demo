#include <nan.h>
#include <string>

namespace __reverse__ {

using v8::Local;
using v8::String;

NAN_METHOD(Reverse)
{
    Nan::MaybeLocal<String> handle = Nan::To<String>(info[0]);
    Local<String> local_handle = handle.ToLocalChecked();

    Nan::Utf8String val(local_handle);

    // 字符串翻转
    std::string str(*val);
    std::reverse(str.begin(), str.end());

    info.GetReturnValue().Set(Nan::New(str.c_str()).ToLocalChecked());
}

NAN_MODULE_INIT(Init)
{
    Nan::Export(target, "reverse", Reverse);
}

NODE_MODULE(reverse, Init)

}
