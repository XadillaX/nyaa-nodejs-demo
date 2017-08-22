/**
 * XadillaX <i@2333.moe> created at 2017-08-22 16:19:31 with ❤
 *
 * Copyright (c) 2017 xcoder.in, all rights reserved.
 */
"use strict";

const EventEmitter = require("events").EventEmitter;
const fs = require("fs");
const path = require("path");

const EFSWCore = require("../build/Release/core").EFSWCore;

const ACTION_MAP = {
    "1": "ADD",
    "2": "DELETE",
    "3": "MODIFIED",
    "4": "MOVED"
};

class Watcher extends EventEmitter {
    constructor(_path) {
        _path = path.resolve(process.cwd(), _path);

        super();
        Object.defineProperties(this, {
            path: {
                value: _path,
                configurable: false,
                enumerable: true,
                writable: false
            },
            core: {
                value: new EFSWCore(_path, this._onEFSWEvent.bind(this)),
                configurable: false,
                enumerable: false,
                writable: false
            }
        });

        const self = this;
        fs.stat(_path, function(err, stat) {
            if(err) return self.emit("error", err);
            if(!stat.isDirectory()) {
                return self.emit("error", new Error(`${_path} is not a directory.`));
            }
        });
    }

    _onEFSWEvent(_path, filename, oldFilename, action) {
        const fullPath = path.join(_path, filename);
        const info = {
            dir: _path,
            action: ACTION_MAP[action] || "UNKNOWN",
            relative: filename
        };

        if(oldFilename) {
            info.old = path.join(_path, oldFilename);
            info.oldRelative = oldFilename;
        }

        if(info.action === "UNKNOWN") {
            const err = new Error(`Unknown fs event ${action}.`);
            err.info = info;
            this.emit("error", err);
        } else {
            this.emit("change", fullPath, info);
        }
    }
}

module.exports = Watcher;
