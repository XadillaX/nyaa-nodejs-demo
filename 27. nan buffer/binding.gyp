{
  "targets": [{
    "target_name": "buffer",
    "sources": [
      "buffer.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}