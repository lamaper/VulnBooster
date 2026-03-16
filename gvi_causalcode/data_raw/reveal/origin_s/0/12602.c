static VALUE ossl_x509name_initialize_copy ( VALUE self , VALUE other ) {
 X509_NAME * name , * name_other , * name_new ;
 rb_check_frozen ( self ) ;
 GetX509Name ( self , name ) ;
 SafeGetX509Name ( other , name_other ) ;
 name_new = X509_NAME_dup ( name_other ) ;
 if ( ! name_new ) ossl_raise ( eX509NameError , "X509_NAME_dup" ) ;
 SetX509Name ( self , name_new ) ;
 X509_NAME_free ( name ) ;
 return self ;
 }