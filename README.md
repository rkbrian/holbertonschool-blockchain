# holbertonschool-blockchain

## General
 - How a Blockchain is
 - What is a hash algorithm
 - What SHA stands for
 - How hash algorithms apply to Blockchains
 - What is asymmetric cryptography
 - How asymmetric cryptography applies to cryptocurrencies
 - What ECC stands for
 - What ECDSA stands for
 - What a digital signature is
 - How digital signatures apply to cryptocurrencies

## Content (Stage 1)
holbertonschool-blockchain
 - crypto
 - - ec_create.c
 - - ec_from_pub.c
 - - ec_load.c
 - - ec_save.c
 - - ec_sign.c
 - - ec_to_pub.c
 - - ec_verify.c
 - - hblk_crypto.h
 - - libhblk_crypto.a
 - - provided
 - - - _print_hex_buffer.c
 - - sha256.c
 - - test
 - - - ec_create-main.c
 - - - ec_from_pub-main.c
 - - - ec_load-main.c
 - - - ec_save-main.c
 - - - ec_sign-main.c
 - - - ec_to_pub-main.c
 - - - ec_verify-main.c
 - - - sha256-main.c
 - README.md

## Extra
### Generate: libhblk_crypto.a
 - make libhblk_crypto.a
 - ar -t libhblk_crypto.a
 - nm --defined-only libhblk_crypto.a | grep T | cut -d ' ' -f3
