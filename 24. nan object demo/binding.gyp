{
  "targets": [{
    "target_name": "object",
    "sources": [
      "object.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}