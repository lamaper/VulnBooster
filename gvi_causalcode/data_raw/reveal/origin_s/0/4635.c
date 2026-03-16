static VALUE ossl_cipher_iv_length ( VALUE self ) {
 EVP_CIPHER_CTX * ctx ;
 int len = 0 ;
 GetCipher ( self , ctx ) ;


 return INT2NUM ( len ) ;
 }