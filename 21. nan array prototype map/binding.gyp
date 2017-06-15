{
    "targets": [{
    "target_name": "map",
    "sources": [
      "map.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}