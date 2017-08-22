/**
 * node-efsw - Node.js binding for EFSW
 *
 * Copyright (c) 2017 XadillaX <i@2333.moe>
 *
 * MIT License <https://github.com/XadillaX/node-efsw/blob/master/LICENSE>
 */
#include "efsw_core.h"
using namespace efsw;
using namespace v8;

namespace efsw_core {

EFSWCore::EFSWCore(const char* path, Nan::Callback* listener) :
    path(path),
    listener(listener),
    core_listener(listener)
{
    watcher = new FileWatcher();
    watch_id = watcher->AddWatch(path, &core_listener, true);
}

EFSWCore::~EFSWCore()
{
    Nan::HandleScope scope;
    delete watcher;
    delete listener;
}

NAN_METHOD(EFSWCore::New)
{
    Nan::Utf8String path(info[0]->ToString());
    Nan::Callback* listener = new Nan::Callback(info[1].As<v8::Function>());

    EFSWCore* core = new EFSWCore(*path, listener);
    core->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_MODULE_INIT(EFSWCore::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("EFSWCore").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::Set(target, Nan::New("EFSWCore").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

}
