{
  "targets": [{
    "target_name": "nbody",
    "sources": [
      "nbody.cc",
      "addon.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}