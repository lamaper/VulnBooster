static VALUE ossl_x509name_hash ( VALUE self ) {
 X509_NAME * name ;
 unsigned long hash ;
 GetX509Name ( self , name ) ;
 hash = X509_NAME_hash ( name ) ;
 return ULONG2NUM ( hash ) ;
 }