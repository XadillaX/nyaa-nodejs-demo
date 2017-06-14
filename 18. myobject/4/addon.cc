#include <node.h>
#include "myobject.h"

namespace __addon4__ {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports, Local<Object> module)
{
    MyObject::Init(exports->GetIsolate());
    NODE_SET_METHOD(module, "exports", MyObject::NewInstance);
}

NODE_MODULE(addon1, InitAll)

}
