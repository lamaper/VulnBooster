X509_NAME * GetX509NamePtr ( VALUE obj ) {
 X509_NAME * name ;
 SafeGetX509Name ( obj , name ) ;
 return name ;
 }