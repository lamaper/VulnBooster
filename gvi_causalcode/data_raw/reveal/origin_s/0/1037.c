static int ossl_x509name_cmp0 ( VALUE self , VALUE other ) {
 X509_NAME * name1 , * name2 ;
 GetX509Name ( self , name1 ) ;
 SafeGetX509Name ( other , name2 ) ;
 return X509_NAME_cmp ( name1 , name2 ) ;
 }