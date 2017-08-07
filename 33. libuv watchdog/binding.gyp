{
  "targets": [{
    "target_name": "efsw",
    "type": "static_library",
    "sources": [
      "../deps/efsw/src/efsw/Debug.cpp",
      "../deps/efsw/src/efsw/DirectorySnapshot.cpp",
      "../deps/efsw/src/efsw/DirectorySnapshotDiff.cpp",
      "../deps/efsw/src/efsw/DirWatcherGeneric.cpp",
      "../deps/efsw/src/efsw/FileInfo.cpp",
      "../deps/efsw/src/efsw/FileSystem.cpp",
      "../deps/efsw/src/efsw/FileWatcher.cpp",
      "../deps/efsw/src/efsw/FileWatcherFSEvents.cpp",
      "../deps/efsw/src/efsw/FileWatcherGeneric.cpp",
      "../deps/efsw/src/efsw/FileWatcherImpl.cpp",
      "../deps/efsw/src/efsw/FileWatcherInotify.cpp",
      "../deps/efsw/src/efsw/Log.cpp",
      "../deps/efsw/src/efsw/Mutex.cpp",
      "../deps/efsw/src/efsw/String.cpp",
      "../deps/efsw/src/efsw/System.cpp",
      "../deps/efsw/src/efsw/Thread.cpp",
      "../deps/efsw/src/efsw/Watcher.cpp",
      "../deps/efsw/src/efsw/WatcherFSEvents.cpp",
      "../deps/efsw/src/efsw/WatcherGeneric.cpp",
      "../deps/efsw/src/efsw/WatcherInotify.cpp"
    ],
    "include_dirs": [
      "../deps/efsw/include",
      "../deps/efsw/src"
    ],
    "conditions": [
      ["OS==\"win\"", {
        "sources": [
          "../deps/efsw/src/efsw/platform/win/FileSystemImpl.cpp",
          "../deps/efsw/src/efsw/platform/win/MutexImpl.cpp",
          "../deps/efsw/src/efsw/platform/win/SystemImpl.cpp",
          "../deps/efsw/src/efsw/platform/win/ThreadImpl.cpp",
          "../deps/efsw/src/efsw/FileWatcherWin32.cpp",
          "../deps/efsw/src/efsw/WatcherWin32.cpp"
        ]
      }],
      ["OS!=\"win\"", {
        "sources": [
          "../deps/efsw/src/efsw/platform/posix/FileSystemImpl.cpp",
          "../deps/efsw/src/efsw/platform/posix/MutexImpl.cpp",
          "../deps/efsw/src/efsw/platform/posix/SystemImpl.cpp",
          "../deps/efsw/src/efsw/platform/posix/ThreadImpl.cpp",
          "../deps/efsw/src/efsw/FileWatcherKqueue.cpp",
          "../deps/efsw/src/efsw/WatcherKqueue.cpp" 
        ]
      }],
      ["OS==\"mac\"", {
        "defines": [
          "EFSW_FSEVENTS_SUPPORTED"
        ],
        "xcode_settings": {
          "OTHER_LDFLAGS": [
            "-framework CoreFoundation -framework CoreServices"
          ]
        }
      }]
    ]
  }, {
    "target_name": "watchdog",
    "sources": [
      "watchdog.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ],
    "dependencies": [
      "efsw"
    ],
    "conditions": [
      ["OS==\"mac\"", {
        "xcode_settings": {
          "OTHER_LDFLAGS": [
            "-framework CoreFoundation -framework CoreServices"
          ]
        }
      }]
    ]
  }]
}