METHOD ( x509_t , create_subjectAltName_enumerator , enumerator_t * , private_x509_cert_t * this ) {
 return this -> subjectAltNames -> create_enumerator ( this -> subjectAltNames ) ;
 }