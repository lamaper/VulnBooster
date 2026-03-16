const EVP_CIPHER * EVP_aes_ ## keylen ## _ ## mode ( void ) \ {
 return & aes_ ## keylen ## _ ## mode ;
 }

 \ nid ## _ ## keylen ## _ ## mode , blocksize , \ ( EVP_CIPH_ ## MODE ## _MODE == EVP_CIPH_XTS_MODE ? 2 : 1 ) * keylen / 8 , ivlen , \ flags | EVP_CIPH_ ## MODE ## _MODE , \ aes_ ## mode ## _init_key , \ aes_ ## mode ## _cipher , \ aes_ ## mode ## _cleanup , \ sizeof ( EVP_AES_ ## MODE ## _CTX ) , \ NULL , NULL , aes_ ## mode ## _ctrl , NULL }
 ;
 const EVP_CIPHER * EVP_aes_ ## keylen ## _ ## mode ( void ) \ {
 return & aes_ ## keylen ## _ ## mode ;
 }

 int HWAES_set_decrypt_key ( const unsigned char * userKey , const int bits , AES_KEY * key ) ;
 void HWAES_encrypt ( const unsigned char * in , unsigned char * out , const AES_KEY * key ) ;
 void HWAES_decrypt ( const unsigned char * in , unsigned char * out , const AES_KEY * key ) ;
 void HWAES_cbc_encrypt ( const unsigned char * in , unsigned char * out , size_t length , const AES_KEY * key , unsigned char * ivec , const int enc ) ;
 void HWAES_ctr32_encrypt_blocks ( const unsigned char * in , unsigned char * out , size_t len , const AES_KEY * key , const unsigned char ivec [ 16 ] ) ;
 void HWAES_xts_encrypt ( const unsigned char * inp , unsigned char * out , size_t len , const AES_KEY * key1 , const AES_KEY * key2 , const unsigned char iv [ 16 ] ) ;
 void HWAES_xts_decrypt ( const unsigned char * inp , unsigned char * out , size_t len , const AES_KEY * key1 , const AES_KEY * key2 , const unsigned char iv [ 16 ] ) ;

 int ret , mode ;
 EVP_AES_KEY * dat = EVP_C_DATA ( EVP_AES_KEY , ctx ) ;
 mode = EVP_CIPHER_CTX_mode ( ctx ) ;
 if ( ( mode == EVP_CIPH_ECB_MODE || mode == EVP_CIPH_CBC_MODE ) && ! enc ) {

 ret = HWAES_set_decrypt_key ( key , EVP_CIPHER_CTX_key_length ( ctx ) * 8 , & dat -> ks . ks ) ;
 dat -> block = ( block128_f ) HWAES_decrypt ;
 dat -> stream . cbc = NULL ;


 else # endif # ifdef BSAES_CAPABLE if ( BSAES_CAPABLE && mode == EVP_CIPH_CBC_MODE ) {
 ret = AES_set_decrypt_key ( key , EVP_CIPHER_CTX_key_length ( ctx ) * 8 , & dat -> ks . ks ) ;
 dat -> block = ( block128_f ) AES_decrypt ;
 dat -> stream . cbc = ( cbc128_f ) bsaes_cbc_encrypt ;
 }
 else # endif # ifdef VPAES_CAPABLE if ( VPAES_CAPABLE ) {
 ret = vpaes_set_decrypt_key ( key , EVP_CIPHER_CTX_key_length ( ctx ) * 8 , & dat -> ks . ks ) ;
 dat -> block = ( block128_f ) vpaes_decrypt ;
 dat -> stream . cbc = mode == EVP_CIPH_CBC_MODE ? ( cbc128_f ) vpaes_cbc_encrypt : NULL ;
 }
 else # endif {
 ret = AES_set_decrypt_key ( key , EVP_CIPHER_CTX_key_length ( ctx ) * 8 , & dat -> ks . ks ) ;
 dat -> block = ( block128_f ) AES_decrypt ;
 dat -> stream . cbc = mode == EVP_CIPH_CBC_MODE ? ( cbc128_f ) AES_cbc_encrypt : NULL ;
 }
 }
 else # ifdef HWAES_CAPABLE if ( HWAES_CAPABLE ) {
 ret = HWAES_set_encrypt_key ( key , EVP_CIPHER_CTX_key_length ( ctx ) * 8 , & dat -> ks . ks ) ;
 dat -> block = ( block128_f ) HWAES_encrypt ;
 dat -> stream . cbc = NULL ;

 else # endif # ifdef HWAES_ctr32_encrypt_blocks if ( mode == EVP_CIPH_CTR_MODE ) dat -> stream . ctr = ( ctr128_f ) HWAES_ctr32_encrypt_blocks ;
 else # endif ( void ) 0 ;
 }
 else # endif # ifdef BSAES_CAPABLE if ( BSAES_CAPABLE && mode == EVP_CIPH_CTR_MODE ) {
 ret = AES_set_encrypt_key ( key , EVP_CIPHER_CTX_key_length ( ctx ) * 8 , & dat -> ks . ks ) ;
 dat -> block = ( block128_f ) AES_encrypt ;
 dat -> stream . ctr = ( ctr128_f ) bsaes_ctr32_encrypt_blocks ;
 }
 else # endif # ifdef VPAES_CAPABLE if ( VPAES_CAPABLE ) {
 ret = vpaes_set_encrypt_key ( key , EVP_CIPHER_CTX_key_length ( ctx ) * 8 , & dat -> ks . ks ) ;
 dat -> block = ( block128_f ) vpaes_encrypt ;
 dat -> stream . cbc = mode == EVP_CIPH_CBC_MODE ? ( cbc128_f ) vpaes_cbc_encrypt : NULL ;
 }
 else # endif {
 ret = AES_set_encrypt_key ( key , EVP_CIPHER_CTX_key_length ( ctx ) * 8 , & dat -> ks . ks ) ;
 dat -> block = ( block128_f ) AES_encrypt ;
 dat -> stream . cbc = mode == EVP_CIPH_CBC_MODE ? ( cbc128_f ) AES_cbc_encrypt : NULL ;


 if ( ret < 0 ) {
 EVPerr ( EVP_F_AES_INIT_KEY , EVP_R_AES_KEY_SETUP_FAILED ) ;
 return 0 ;
 }
 return 1 ;
 }
 static int aes_cbc_cipher ( EVP_CIPHER_CTX * ctx , unsigned char * out , const unsigned char * in , size_t len ) {
 EVP_AES_KEY * dat = EVP_C_DATA ( EVP_AES_KEY , ctx ) ;
 if ( dat -> stream . cbc ) ( * dat -> stream . cbc ) ( in , out , len , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , EVP_CIPHER_CTX_encrypting ( ctx ) ) ;
 else if ( EVP_CIPHER_CTX_encrypting ( ctx ) ) CRYPTO_cbc128_encrypt ( in , out , len , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , dat -> block ) ;
 else CRYPTO_cbc128_decrypt ( in , out , len , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , dat -> block ) ;
 return 1 ;
 }
 static int aes_ecb_cipher ( EVP_CIPHER_CTX * ctx , unsigned char * out , const unsigned char * in , size_t len ) {
 size_t bl = EVP_CIPHER_CTX_block_size ( ctx ) ;
 size_t i ;
 EVP_AES_KEY * dat = EVP_C_DATA ( EVP_AES_KEY , ctx ) ;
 if ( len < bl ) return 1 ;
 for ( i = 0 , len -= bl ;
 i <= len ;
 i += bl ) ( * dat -> block ) ( in + i , out + i , & dat -> ks ) ;
 return 1 ;
 }
 static int aes_ofb_cipher ( EVP_CIPHER_CTX * ctx , unsigned char * out , const unsigned char * in , size_t len ) {
 EVP_AES_KEY * dat = EVP_C_DATA ( EVP_AES_KEY , ctx ) ;
 int num = EVP_CIPHER_CTX_num ( ctx ) ;
 CRYPTO_ofb128_encrypt ( in , out , len , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , & num , dat -> block ) ;
 EVP_CIPHER_CTX_set_num ( ctx , num ) ;
 return 1 ;
 }
 static int aes_cfb_cipher ( EVP_CIPHER_CTX * ctx , unsigned char * out , const unsigned char * in , size_t len ) {
 EVP_AES_KEY * dat = EVP_C_DATA ( EVP_AES_KEY , ctx ) ;
 int num = EVP_CIPHER_CTX_num ( ctx ) ;
 CRYPTO_cfb128_encrypt ( in , out , len , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , & num , EVP_CIPHER_CTX_encrypting ( ctx ) , dat -> block ) ;
 EVP_CIPHER_CTX_set_num ( ctx , num ) ;
 return 1 ;
 }
 static int aes_cfb8_cipher ( EVP_CIPHER_CTX * ctx , unsigned char * out , const unsigned char * in , size_t len ) {
 EVP_AES_KEY * dat = EVP_C_DATA ( EVP_AES_KEY , ctx ) ;
 int num = EVP_CIPHER_CTX_num ( ctx ) ;
 CRYPTO_cfb128_8_encrypt ( in , out , len , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , & num , EVP_CIPHER_CTX_encrypting ( ctx ) , dat -> block ) ;
 EVP_CIPHER_CTX_set_num ( ctx , num ) ;
 return 1 ;
 }
 static int aes_cfb1_cipher ( EVP_CIPHER_CTX * ctx , unsigned char * out , const unsigned char * in , size_t len ) {
 EVP_AES_KEY * dat = EVP_C_DATA ( EVP_AES_KEY , ctx ) ;
 if ( EVP_CIPHER_CTX_test_flags ( ctx , EVP_CIPH_FLAG_LENGTH_BITS ) ) {
 int num = EVP_CIPHER_CTX_num ( ctx ) ;
 CRYPTO_cfb128_1_encrypt ( in , out , len , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , & num , EVP_CIPHER_CTX_encrypting ( ctx ) , dat -> block ) ;
 EVP_CIPHER_CTX_set_num ( ctx , num ) ;
 return 1 ;
 }
 while ( len >= MAXBITCHUNK ) {
 int num = EVP_CIPHER_CTX_num ( ctx ) ;
 CRYPTO_cfb128_1_encrypt ( in , out , MAXBITCHUNK * 8 , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , & num , EVP_CIPHER_CTX_encrypting ( ctx ) , dat -> block ) ;
 EVP_CIPHER_CTX_set_num ( ctx , num ) ;
 len -= MAXBITCHUNK ;
 }
 if ( len ) {
 int num = EVP_CIPHER_CTX_num ( ctx ) ;
 CRYPTO_cfb128_1_encrypt ( in , out , len * 8 , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , & num , EVP_CIPHER_CTX_encrypting ( ctx ) , dat -> block ) ;
 EVP_CIPHER_CTX_set_num ( ctx , num ) ;
 }
 return 1 ;
 }
 static int aes_ctr_cipher ( EVP_CIPHER_CTX * ctx , unsigned char * out , const unsigned char * in , size_t len ) {
 unsigned int num = EVP_CIPHER_CTX_num ( ctx ) ;
 EVP_AES_KEY * dat = EVP_C_DATA ( EVP_AES_KEY , ctx ) ;
 if ( dat -> stream . ctr ) CRYPTO_ctr128_encrypt_ctr32 ( in , out , len , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , EVP_CIPHER_CTX_buf_noconst ( ctx ) , & num , dat -> stream . ctr ) ;
 else CRYPTO_ctr128_encrypt ( in , out , len , & dat -> ks , EVP_CIPHER_CTX_iv_noconst ( ctx ) , EVP_CIPHER_CTX_buf_noconst ( ctx ) , & num , dat -> block ) ;
 EVP_CIPHER_CTX_set_num ( ctx , num ) ;
 return 1 ;
 }
 BLOCK_CIPHER_generic_pack ( NID_aes , 128 , 0 )