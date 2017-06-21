#include <nan.h>
#include "nbody.h"

namespace __nbody__ {

using v8::Function;
using v8::Local;
using v8::Value;

class NBodyWorker : public Nan::AsyncWorker {
public:
    NBodyWorker(unsigned int times, Nan::Callback* callback) :
        times(times),
        energy(0),
        Nan::AsyncWorker(callback)
    {
    }

    ~NBodyWorker() {}

    void Execute()
    {
        NBodySystem bodies;
        for(unsigned int i = 0; i < times; i++) bodies.advance(0.01);
        energy = bodies.energy();
    }

    void HandleOKCallback()
    {
        Nan::HandleScope scope;

        Local<Value> argv[2] = {
            Nan::Undefined(),
            Nan::New(energy)
        };
        callback->Call(2, argv);
    }

private:
    unsigned int times;
    double energy;
};

NAN_METHOD(Calc)
{
    Nan::Callback* callback;
    unsigned int times = 50000000;
    if(info.Length() > 1)
    {
        double _times = Nan::To<double>(info[0]).FromJust();
        if(_times < 0)
        {
            Nan::ThrowRangeError("Wrong times.");
            return;
        }

        times = _times;
        callback = new Nan::Callback(info[1].As<Function>());
    }
    else
    if(info.Length() > 0)
    {
        callback = new Nan::Callback(info[0].As<Function>());
    }
    else
    {
        Nan::ThrowTypeError("Callback needed.");
    }

    Nan::AsyncQueueWorker(new NBodyWorker(times, callback));
}

NAN_MODULE_INIT(Init)
{
    Nan::Export(target, "calc", Calc);
}

NODE_MODULE(reverse, Init)

}
