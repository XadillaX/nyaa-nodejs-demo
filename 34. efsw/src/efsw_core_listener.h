/**
 * node-efsw - Node.js binding for EFSW
 *
 * Copyright (c) 2017 XadillaX <i@2333.moe>
 *
 * MIT License <https://github.com/XadillaX/node-efsw/blob/master/LICENSE>
 */
#ifndef __EFSW_CORE_LISTENER_H__
#define __EFSW_CORE_LISTENER_H__
#include <string>
#include <nan.h>
#include "./deps/efsw/include/efsw/efsw.hpp"

namespace efsw_core {

#define Watch watch
#define AddWatch addWatch
#define HandleFileAction handleFileAction
#define GetLastErrorLog getLastErrorLog
#define WatchId WatchID

class EFSWCoreListener : public efsw::FileWatchListener {
public:
    EFSWCoreListener(Nan::Callback* listener);
    ~EFSWCoreListener();

    void HandleFileAction(
            efsw::WatchId,
            const std::string& dir,
            const std::string& filename,
            efsw::Action action,
            std::string old_filename);

private:
    Nan::Callback* listener;
};

}

#endif
