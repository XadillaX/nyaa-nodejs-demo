{
  "targets": [{
    "target_name": "mbedtls",
    "type": "static_library",
    "sources": [
      "../deps/mbedtls/library/debug.c",
      "../deps/mbedtls/library/net.c",
      "../deps/mbedtls/library/ssl_cache.c",
      "../deps/mbedtls/library/ssl_ciphersuites.c",
      "../deps/mbedtls/library/ssl_cli.c",
      "../deps/mbedtls/library/ssl_cookie.c",
      "../deps/mbedtls/library/ssl_srv.c",
      "../deps/mbedtls/library/ssl_ticket.c",
      "../deps/mbedtls/library/ssl_tls.c"
    ],
    "include_dirs": [
      "../deps/mbedtls/include",
      "../deps"
    ],
    "defines": [
      "MBEDTLS_CONFIG_FILE=\"mbedtls/configs/config-mini-tls1_1.h\""
    ]
  }, {
    "target_name": "mbedx509",
    "type": "static_library",
    "sources": [
      "../deps/mbedtls/library/certs.c",
      "../deps/mbedtls/library/pkcs11.c",
      "../deps/mbedtls/library/x509.c",
      "../deps/mbedtls/library/x509_create.c",
      "../deps/mbedtls/library/x509_crl.c",
      "../deps/mbedtls/library/x509_crt.c",
      "../deps/mbedtls/library/x509_csr.c",
      "../deps/mbedtls/library/x509write_crt.c",
      "../deps/mbedtls/library/x509write_csr.c"
    ],
    "include_dirs": [
      "../deps/mbedtls/include",
      "../deps"
    ],
    "defines": [
      "MBEDTLS_CONFIG_FILE=\"mbedtls/configs/config-mini-tls1_1.h\""
    ]
  }, {
    "target_name": "mbedcrypto",
    "type": "static_library",
    "sources": [
      "../deps/mbedtls/library/aes.c",
      "../deps/mbedtls/library/aesni.c",
      "../deps/mbedtls/library/arc4.c",
      "../deps/mbedtls/library/asn1parse.c",
      "../deps/mbedtls/library/asn1write.c",
      "../deps/mbedtls/library/base64.c",
      "../deps/mbedtls/library/bignum.c",
      "../deps/mbedtls/library/blowfish.c",
      "../deps/mbedtls/library/camellia.c",
      "../deps/mbedtls/library/ccm.c",
      "../deps/mbedtls/library/cipher.c",
      "../deps/mbedtls/library/cipher_wrap.c",
      "../deps/mbedtls/library/ctr_drbg.c",
      "../deps/mbedtls/library/des.c",
      "../deps/mbedtls/library/dhm.c",
      "../deps/mbedtls/library/ecdh.c",
      "../deps/mbedtls/library/ecdsa.c",
      "../deps/mbedtls/library/ecp.c",
      "../deps/mbedtls/library/ecp_curves.c",
      "../deps/mbedtls/library/entropy.c",
      "../deps/mbedtls/library/entropy_poll.c",
      "../deps/mbedtls/library/error.c",
      "../deps/mbedtls/library/gcm.c",
      "../deps/mbedtls/library/havege.c",
      "../deps/mbedtls/library/hmac_drbg.c",
      "../deps/mbedtls/library/md.c",
      "../deps/mbedtls/library/md2.c",
      "../deps/mbedtls/library/md4.c",
      "../deps/mbedtls/library/md5.c",
      "../deps/mbedtls/library/md_wrap.c",
      "../deps/mbedtls/library/memory_buffer_alloc.c",
      "../deps/mbedtls/library/oid.c",
      "../deps/mbedtls/library/padlock.c",
      "../deps/mbedtls/library/pem.c",
      "../deps/mbedtls/library/pk.c",
      "../deps/mbedtls/library/pk_wrap.c",
      "../deps/mbedtls/library/pkcs12.c",
      "../deps/mbedtls/library/pkcs5.c",
      "../deps/mbedtls/library/pkparse.c",
      "../deps/mbedtls/library/pkwrite.c",
      "../deps/mbedtls/library/platform.c",
      "../deps/mbedtls/library/ripemd160.c",
      "../deps/mbedtls/library/rsa.c",
      "../deps/mbedtls/library/sha1.c",
      "../deps/mbedtls/library/sha256.c",
      "../deps/mbedtls/library/sha512.c",
      "../deps/mbedtls/library/threading.c",
      "../deps/mbedtls/library/timing.c",
      "../deps/mbedtls/library/version.c",
      "../deps/mbedtls/library/version_features.c",
      "../deps/mbedtls/library/xtea.c"
    ],
    "include_dirs": [
      "../deps/mbedtls/include",
      "../deps"
    ],
    "defines": [
      "MBEDTLS_CONFIG_FILE=\"mbedtls/configs/config-mini-tls1_1.h\""
    ]
  }, {
    "target_name": "mapped_property_interceptor",
    "sources": [
      "../deps/minihttp/minihttp.cpp",
      "interceptor.cpp"
    ],
    "include_dirs": [
      "../deps/mbedtls/include"
    ],
    "defines": [ "MINIHTTP_USE_MBEDTLS" ],
    "dependencies": [
      "mbedtls",
      "mbedx509",
      "mbedcrypto"
    ]
  }]
}