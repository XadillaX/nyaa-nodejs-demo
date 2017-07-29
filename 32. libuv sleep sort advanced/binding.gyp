{
  "targets": [{
    "target_name": "mutex_sleep",
    "sources": [
      "mutex/sleep.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }, {
    "target_name": "rwlock_sleep",
    "sources": [
      "rwlock/sleep.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }, {
    "target_name": "sem_sleep",
    "sources": [
      "sem/sleep.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}