/**
 * node-efsw - Node.js binding for EFSW
 *
 * Copyright (c) 2017 XadillaX <i@2333.moe>
 *
 * MIT License <https://github.com/XadillaX/node-efsw/blob/master/LICENSE>
 */
#ifndef __ENTRY_H__
#define __ENTRY_H__

#include "nan.h"
#include "efsw_core.h"

namespace efsw_core {

NAN_MODULE_INIT(Init)
{
    EFSWCore::Init(target);
}

NODE_MODULE(core, Init)

}

#endif
