{
    "targets": [{
    "target_name": "prototype",
    "sources": [
      "prototype/addon.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }, {
    "target_name": "accessor",
    "sources": [
      "accessor/addon.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}