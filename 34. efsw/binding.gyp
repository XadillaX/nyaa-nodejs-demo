{
  "targets": [{
    "target_name": "efsw",
    "type": "static_library",
    "sources": [
      "./src/deps/efsw/src/efsw/Debug.cpp",
      "./src/deps/efsw/src/efsw/DirectorySnapshot.cpp",
      "./src/deps/efsw/src/efsw/DirectorySnapshotDiff.cpp",
      "./src/deps/efsw/src/efsw/DirWatcherGeneric.cpp",
      "./src/deps/efsw/src/efsw/FileInfo.cpp",
      "./src/deps/efsw/src/efsw/FileSystem.cpp",
      "./src/deps/efsw/src/efsw/FileWatcher.cpp",
      "./src/deps/efsw/src/efsw/FileWatcherFSEvents.cpp",
      "./src/deps/efsw/src/efsw/FileWatcherGeneric.cpp",
      "./src/deps/efsw/src/efsw/FileWatcherImpl.cpp",
      "./src/deps/efsw/src/efsw/FileWatcherInotify.cpp",
      "./src/deps/efsw/src/efsw/Log.cpp",
      "./src/deps/efsw/src/efsw/Mutex.cpp",
      "./src/deps/efsw/src/efsw/String.cpp",
      "./src/deps/efsw/src/efsw/System.cpp",
      "./src/deps/efsw/src/efsw/Thread.cpp",
      "./src/deps/efsw/src/efsw/Watcher.cpp",
      "./src/deps/efsw/src/efsw/WatcherFSEvents.cpp",
      "./src/deps/efsw/src/efsw/WatcherGeneric.cpp",
      "./src/deps/efsw/src/efsw/WatcherInotify.cpp"
    ],
    "include_dirs": [
      "./src/deps/efsw/include",
      "./src/deps/efsw/src"
    ],
    "conditions": [
      ["OS==\"win\"", {
        "sources": [
          "./src/deps/efsw/src/efsw/platform/win/FileSystemImpl.cpp",
          "./src/deps/efsw/src/efsw/platform/win/MutexImpl.cpp",
          "./src/deps/efsw/src/efsw/platform/win/SystemImpl.cpp",
          "./src/deps/efsw/src/efsw/platform/win/ThreadImpl.cpp",
          "./src/deps/efsw/src/efsw/FileWatcherWin32.cpp",
          "./src/deps/efsw/src/efsw/WatcherWin32.cpp"
        ]
      }],
      ["OS!=\"win\"", {
        "sources": [
          "./src/deps/efsw/src/efsw/platform/posix/FileSystemImpl.cpp",
          "./src/deps/efsw/src/efsw/platform/posix/MutexImpl.cpp",
          "./src/deps/efsw/src/efsw/platform/posix/SystemImpl.cpp",
          "./src/deps/efsw/src/efsw/platform/posix/ThreadImpl.cpp",
          "./src/deps/efsw/src/efsw/FileWatcherKqueue.cpp",
          "./src/deps/efsw/src/efsw/WatcherKqueue.cpp" 
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
    "target_name": "core",
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ],
    "sources": [
      "./src/entry.cc",
      "./src/efsw_core.cc",
      "./src/efsw_core_listener.cc"
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
