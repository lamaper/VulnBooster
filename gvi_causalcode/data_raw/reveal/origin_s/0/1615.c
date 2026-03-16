static VALUE ossl_cipher_set_iv ( VALUE self , VALUE iv ) {
 EVP_CIPHER_CTX * ctx ;
 int iv_len = 0 ;
 StringValue ( iv ) ;
 GetCipher ( self , ctx ) ;


 if ( RSTRING_LEN ( iv ) != iv_len ) ossl_raise ( rb_eArgError , "iv must be %d bytes" , iv_len ) ;
 if ( EVP_CipherInit_ex ( ctx , NULL , NULL , NULL , ( unsigned char * ) RSTRING_PTR ( iv ) , - 1 ) != 1 ) ossl_raise ( eCipherError , NULL ) ;
 return iv ;
 }