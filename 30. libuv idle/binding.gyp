{
  "targets": [{
    "target_name": "idle",
    "sources": [
      "idle.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}