VALUE ossl_x509name_new ( X509_NAME * name ) {
 X509_NAME * new ;
 VALUE obj ;
 obj = NewX509Name ( cX509Name ) ;
 if ( ! name ) {
 new = X509_NAME_new ( ) ;
 }
 else {
 new = X509_NAME_dup ( name ) ;
 }
 if ( ! new ) {
 ossl_raise ( eX509NameError , NULL ) ;
 }
 SetX509Name ( obj , new ) ;
 return obj ;
 }