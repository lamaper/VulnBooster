static VALUE ossl_x509name_to_s_old ( VALUE self ) {
 X509_NAME * name ;
 char * buf ;
 VALUE str ;
 GetX509Name ( self , name ) ;
 buf = X509_NAME_oneline ( name , NULL , 0 ) ;
 str = rb_str_new2 ( buf ) ;
 OPENSSL_free ( buf ) ;
 return str ;
 }