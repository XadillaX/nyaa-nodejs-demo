{
  "targets": [{
    "target_name": "echo",
    "sources": [ "echo.cc" ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}
