#ifndef __MYOBJECT_H__
#define __MYOBJECT_H__

#include <node.h>
#include <node_object_wrap.h>

namespace __addon3__ {

using node::ObjectWrap;
using v8::Object;
using v8::Local;
using v8::Persistent;
using v8::Value;
using v8::Function;
using v8::FunctionCallbackInfo;

class MyObject : public ObjectWrap {
public:
    static void Init(Local<Object> exports);
    double PlusOne();

private:
    explicit MyObject(double value = 0);
    ~MyObject();

    static void New(const FunctionCallbackInfo<Value>& args);
    static void PlusOne(const FunctionCallbackInfo<Value>& args);
    static Persistent<Function> constructor;
    double value_;
};

}

#endif
