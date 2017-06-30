{
  "targets": [{
    "target_name": "json",
    "sources": [
      "json.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}