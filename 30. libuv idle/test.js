/**
 * XadillaX <i@2333.moe> created at 2017-07-12 15:03:00 with ❤
 *
 * Copyright (c) 2017 xcoder.in, all rights reserved.
 */
"use strict";

const addon = require("./build/Release/idle");

addon.startIdle(100);

try {
    addon.startIdle(1);
} catch(e) {
    console.error(e);
}

let times = 100;
function tick() {
    times--;
    console.log(`还剩 ${times} 次 tick。`);

    if(times === 0) return;

    setImmediate(tick);
}

setImmediate(tick);
