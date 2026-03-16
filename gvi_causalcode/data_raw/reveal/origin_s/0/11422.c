static int aes_xts_init_key ( EVP_CIPHER_CTX * ctx , const unsigned char * key , const unsigned char * iv , int enc ) {
 EVP_AES_XTS_CTX * xctx = EVP_C_DATA ( EVP_AES_XTS_CTX , ctx ) ;
 if ( ! iv && ! key ) return 1 ;
 if ( key ) do {



 if ( enc ) {
 HWAES_set_encrypt_key ( key , EVP_CIPHER_CTX_key_length ( ctx ) * 4 , & xctx -> ks1 . ks ) ;
 xctx -> xts . block1 = ( block128_f ) HWAES_encrypt ;


 else {
 HWAES_set_decrypt_key ( key , EVP_CIPHER_CTX_key_length ( ctx ) * 4 , & xctx -> ks1 . ks ) ;
 xctx -> xts . block1 = ( block128_f ) HWAES_decrypt ;


 HWAES_set_encrypt_key ( key + EVP_CIPHER_CTX_key_length ( ctx ) / 2 , EVP_CIPHER_CTX_key_length ( ctx ) * 4 , & xctx -> ks2 . ks ) ;
 xctx -> xts . block2 = ( block128_f ) HWAES_encrypt ;
 xctx -> xts . key1 = & xctx -> ks1 ;
 break ;
 }