{
  "targets": [{
    "target_name": "reverse",
    "sources": [
      "reverse.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}