static VALUE ossl_x509name_to_der ( VALUE self ) {
 X509_NAME * name ;
 VALUE str ;
 long len ;
 unsigned char * p ;
 GetX509Name ( self , name ) ;
 if ( ( len = i2d_X509_NAME ( name , NULL ) ) <= 0 ) ossl_raise ( eX509NameError , NULL ) ;
 str = rb_str_new ( 0 , len ) ;
 p = ( unsigned char * ) RSTRING_PTR ( str ) ;
 if ( i2d_X509_NAME ( name , & p ) <= 0 ) ossl_raise ( eX509NameError , NULL ) ;
 ossl_str_adjust ( str , p ) ;
 return str ;
 }