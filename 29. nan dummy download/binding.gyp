{
  "targets": [{
    "target_name": "download",
    "sources": [
      "download.cc",
      "../deps/minihttp/minihttp.cpp"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")",
      "../deps/mbedtls/include"
    ]
  }]
}