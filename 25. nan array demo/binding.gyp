{
  "targets": [{
    "target_name": "array",
    "sources": [
      "array.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}