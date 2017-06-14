#include <node.h>
#include "myobject.h"

namespace __addon5__ {

using v8::Local;
using v8::Number;
using v8::Object;

void Add(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    
    MyObject* obj1 = ObjectWrap::Unwrap<MyObject>(args[0]->ToObject());
    MyObject* obj2 = ObjectWrap::Unwrap<MyObject>(args[1]->ToObject());
    
    double sum = obj1->value() + obj2->value();
    args.GetReturnValue().Set(Number::New(isolate, sum));
}

void InitAll(Local<Object> exports, Local<Object> module)
{
    MyObject::Init(exports->GetIsolate());

    NODE_SET_METHOD(exports, "createObject", MyObject::NewInstance);
    NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(addon1, InitAll)

}
