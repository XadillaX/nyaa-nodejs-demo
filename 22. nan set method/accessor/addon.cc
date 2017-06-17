#include <nan.h>

namespace __accessor__ {

using v8::Local;
using v8::Object;
using v8::ObjectTemplate;

int x = 0;

NAN_GETTER(Getter)
{
    info.GetReturnValue().Set(x);
}

NAN_SETTER(Setter)
{
    x = value->Int32Value();
}

NAN_MODULE_INIT(Init)
{
    Local<ObjectTemplate> tpl = Nan::New<ObjectTemplate>();
    Nan::SetAccessor(tpl, Nan::New("x").ToLocalChecked(), Getter, Setter);

    Local<Object> ret = ((Nan::MaybeLocal<Object>)tpl->NewInstance()).ToLocalChecked();
    Nan::Set(target, Nan::New("obj").ToLocalChecked(), ret);
}

NODE_MODULE(accessor, Init)

}
