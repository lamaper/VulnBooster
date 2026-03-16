static VALUE ossl_x509name_alloc ( VALUE klass ) {
 X509_NAME * name ;
 VALUE obj ;
 obj = NewX509Name ( klass ) ;
 if ( ! ( name = X509_NAME_new ( ) ) ) {
 ossl_raise ( eX509NameError , NULL ) ;
 }
 SetX509Name ( obj , name ) ;
 return obj ;
 }