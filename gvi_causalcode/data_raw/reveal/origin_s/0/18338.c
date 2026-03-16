EVP_ENCODE_CTX * EVP_ENCODE_CTX_new ( void ) {
 return OPENSSL_zalloc ( sizeof ( EVP_ENCODE_CTX ) ) ;
 }