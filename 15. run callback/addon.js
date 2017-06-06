/**
 * XadillaX <i@2333.moe> created at 2017-06-06 22:16:19 with ❤
 *
 * Copyright (c) 2017 xcoder.in, all rights reserved.
 */
"use strict";

const addon = require("./build/Release/addon");

module.exports = function(callback) {
    if(!callback || typeof callback !== "function") {
        throw new Error("Wrong argument");
    }

    addon(callback);
};
