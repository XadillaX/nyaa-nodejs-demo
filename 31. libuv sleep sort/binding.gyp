{
  "targets": [{
    "target_name": "sleep",
    "sources": [
      "sleep.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}