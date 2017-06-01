#include <node.h>

namespace __inherit__ {

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

Persistent<Function> cons;

void SetName(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    Local<Object> self = args.Holder();
    self->Set(String::NewFromUtf8(isolate, "name"), args[0]);
}

void Summary(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    Local<Object> self = args.Holder();
    char temp[512];

    String::Utf8Value type(self->Get(String::NewFromUtf8(isolate, "type"))->ToString());
    String::Utf8Value name(self->Get(String::NewFromUtf8(isolate, "name"))->ToString());

    snprintf(temp, 511, "%s is a/an %s.", *name, *type);

    args.GetReturnValue().Set(String::NewFromUtf8(isolate, temp));
}

void Pet(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    Local<Object> self = args.Holder();
    self->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "Unknown"));
    self->Set(String::NewFromUtf8(isolate, "type"), String::NewFromUtf8(isolate, "animal"));

    args.GetReturnValue().Set(self);
}

void Dog(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    Local<Object> self = args.Holder();
    Local<Function> super = cons.Get(isolate);

    super->Call(self, 0, NULL);
    self->Set(String::NewFromUtf8(isolate, "type"), String::NewFromUtf8(isolate, "dog"));

    args.GetReturnValue().Set(self);
}

void Init(Local<Object> exports, Local<Object> module)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<FunctionTemplate> pet = FunctionTemplate::New(isolate, Pet);
    pet->PrototypeTemplate()->Set(
            String::NewFromUtf8(isolate, "setName"),
            FunctionTemplate::New(isolate, SetName));
    pet->PrototypeTemplate()->Set(
            String::NewFromUtf8(isolate, "summary"),
            FunctionTemplate::New(isolate, Summary));

    Local<Function> pet_cons = pet->GetFunction();

    cons.Reset(isolate, pet_cons);

    Local<FunctionTemplate> dog = FunctionTemplate::New(isolate, Dog);
    dog->Inherit(pet);

    Local<Function> dog_cons = dog->GetFunction();

    exports->Set(String::NewFromUtf8(isolate, "Pet"), pet_cons);
    exports->Set(String::NewFromUtf8(isolate, "Dog"), dog_cons);
}

NODE_MODULE(_template, Init)

}
