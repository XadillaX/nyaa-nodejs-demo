#include <nan.h>
#include <string>

namespace __object__ {

using v8::Local;
using v8::Object;
using v8::String;

NAN_METHOD(Calc)
{
    if(!info.Length()) return;

    auto input = info[0]->ToObject();
    auto output = Nan::New<Object>();

    auto x_prop = Nan::New("x").ToLocalChecked();
    auto y_prop = Nan::New("y").ToLocalChecked();
    auto sum_prop = Nan::New("sum").ToLocalChecked();
    auto product_prop = Nan::New("product").ToLocalChecked();

    double x = Nan::Get(input, x_prop).ToLocalChecked()->NumberValue();
    double y = Nan::Get(input, y_prop).ToLocalChecked()->NumberValue();

    Nan::Set(output, sum_prop, Nan::New(x + y));
    Nan::Set(output, product_prop, Nan::New(x * y));

    info.GetReturnValue().Set(output);
}

NAN_MODULE_INIT(Init)
{
    Nan::Export(target, "calc", Calc);
}

NODE_MODULE(reverse, Init)

}
