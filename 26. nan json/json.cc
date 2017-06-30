#include <nan.h>

namespace __array__ {

using v8::Array;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Plus(Local<Value>& obj)
{
    if(obj->IsNumber())
    {
        obj = Nan::New(Nan::To<double>(obj).FromJust() + 1);
        return;
    }
    if(!obj->IsObject()) return;

    if(obj->IsArray())
    {
        auto array = Local<Array>::Cast(obj);
        for(unsigned int i = 0; i < array->Length(); i++)
        {
            Local<Value> val1;
            Local<Value> val2;
            val1 = val2 = Nan::Get(array, i).ToLocalChecked();

            Plus(val1);
            if(val1 != val2)
            {
                Nan::Set(array, i, val1);
            }
        }
        return;
    }

    Local<Object> object = Nan::To<Object>(obj).ToLocalChecked();
    auto properties = Nan::GetOwnPropertyNames(object).ToLocalChecked();
    for(unsigned int i = 0; i < properties->Length(); i++)
    {
        Local<String> key = Nan::To<String>(Nan::Get(properties, i).ToLocalChecked()).ToLocalChecked();
        Local<Value> val1;
        Local<Value> val2;
        val1 = val2 = Nan::Get(object, key).ToLocalChecked();

        Plus(val1);
        if(val1 != val2)
        {
            Nan::Set(object, key, val1);
        }
    }
    return;
}

NAN_METHOD(PlusOne)
{
    Nan::JSON json;
    Nan::MaybeLocal<Value> parsed = json.Parse(Nan::To<String>(info[0]).ToLocalChecked());

    if(parsed.IsEmpty())
    {
        return info.GetReturnValue().Set(info[0]);
    }

    Local<Value> ret = parsed.ToLocalChecked();
    Plus(ret);

    info.GetReturnValue().Set(json.Stringify(Nan::To<Object>(ret).ToLocalChecked()).ToLocalChecked());
}

NAN_MODULE_INIT(Init)
{
    Nan::Export(target, "plusOne", PlusOne);
}

NODE_MODULE(reverse, Init)

}
