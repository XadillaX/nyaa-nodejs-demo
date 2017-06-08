#include <node.h>
#include "myobject.h"

namespace __addon1__ {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports)
{
    MyObject::Init(exports);
}

NODE_MODULE(addon1, InitAll)

}
