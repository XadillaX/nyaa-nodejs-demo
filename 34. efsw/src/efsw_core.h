/**
 * node-efsw - Node.js binding for EFSW
 *
 * Copyright (c) 2017 XadillaX <i@2333.moe>
 *
 * MIT License <https://github.com/XadillaX/node-efsw/blob/master/LICENSE>
 */
#ifndef __EFSW_CORE_H__
#define __EFSW_CORE_H__
#include <string>
#include <nan.h>
#include "./deps/efsw/include/efsw/efsw.hpp"
#include "efsw_core_listener.h"

namespace efsw_core {

class EFSWCore : public Nan::ObjectWrap {
public:
    static NAN_MODULE_INIT(Init);

private:
    explicit EFSWCore(const char* path, Nan::Callback* listener);
    ~EFSWCore();

    static NAN_METHOD(New);

private:
    std::string path;
    Nan::Callback* listener;
    efsw::FileWatcher* watcher;
    efsw::WatchId watch_id;
    EFSWCoreListener core_listener;
};

}

#endif
