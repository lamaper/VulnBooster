static int aes_gcm_cipher ( EVP_CIPHER_CTX * ctx , unsigned char * out , const unsigned char * in , size_t len ) {
 EVP_AES_GCM_CTX * gctx = EVP_C_DATA ( EVP_AES_GCM_CTX , ctx ) ;
 if ( ! gctx -> key_set ) return - 1 ;
 if ( gctx -> tls_aad_len >= 0 ) return aes_gcm_tls_cipher ( ctx , out , in , len ) ;
 if ( ! gctx -> iv_set ) return - 1 ;
 if ( in ) {
 if ( out == NULL ) {
 if ( CRYPTO_gcm128_aad ( & gctx -> gcm , in , len ) ) return - 1 ;
 }
 else if ( EVP_CIPHER_CTX_encrypting ( ctx ) ) {
 if ( gctx -> ctr ) {
 size_t bulk = 0 ;

 size_t res = ( 16 - gctx -> gcm . mres ) % 16 ;
 if ( CRYPTO_gcm128_encrypt ( & gctx -> gcm , in , out , res ) ) return - 1 ;
 bulk = AES_gcm_encrypt ( in + res , out + res , len - res , gctx -> gcm . key , gctx -> gcm . Yi . c , gctx -> gcm . Xi . u ) ;
 gctx -> gcm . len . u [ 1 ] += bulk ;
 bulk += res ;
 }

 }
 else {
 size_t bulk = 0 ;

 size_t res = ( 16 - gctx -> gcm . mres ) % 16 ;
 if ( CRYPTO_gcm128_encrypt ( & gctx -> gcm , in , out , res ) ) return - 1 ;
 bulk = AES_gcm_encrypt ( in + res , out + res , len - res , gctx -> gcm . key , gctx -> gcm . Yi . c , gctx -> gcm . Xi . u ) ;
 gctx -> gcm . len . u [ 1 ] += bulk ;
 bulk += res ;
 }

 }
 }
 else {
 if ( gctx -> ctr ) {
 size_t bulk = 0 ;

 size_t res = ( 16 - gctx -> gcm . mres ) % 16 ;
 if ( CRYPTO_gcm128_decrypt ( & gctx -> gcm , in , out , res ) ) return - 1 ;
 bulk = AES_gcm_decrypt ( in + res , out + res , len - res , gctx -> gcm . key , gctx -> gcm . Yi . c , gctx -> gcm . Xi . u ) ;
 gctx -> gcm . len . u [ 1 ] += bulk ;
 bulk += res ;
 }

 }
 else {
 size_t bulk = 0 ;

 size_t res = ( 16 - gctx -> gcm . mres ) % 16 ;
 if ( CRYPTO_gcm128_decrypt ( & gctx -> gcm , in , out , res ) ) return - 1 ;
 bulk = AES_gcm_decrypt ( in + res , out + res , len - res , gctx -> gcm . key , gctx -> gcm . Yi . c , gctx -> gcm . Xi . u ) ;
 gctx -> gcm . len . u [ 1 ] += bulk ;
 bulk += res ;
 }

 }
 }
 return len ;
 }
 else {
 if ( ! EVP_CIPHER_CTX_encrypting ( ctx ) ) {
 if ( gctx -> taglen < 0 ) return - 1 ;
 if ( CRYPTO_gcm128_finish ( & gctx -> gcm , EVP_CIPHER_CTX_buf_noconst ( ctx ) , gctx -> taglen ) != 0 ) return - 1 ;
 gctx -> iv_set = 0 ;
 return 0 ;
 }
 CRYPTO_gcm128_tag ( & gctx -> gcm , EVP_CIPHER_CTX_buf_noconst ( ctx ) , 16 ) ;
 gctx -> taglen = 16 ;
 gctx -> iv_set = 0 ;
 return 0 ;
 }
 }