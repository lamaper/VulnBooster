METHOD ( x509_t , create_ocsp_uri_enumerator , enumerator_t * , private_x509_cert_t * this ) {
 return this -> ocsp_uris -> create_enumerator ( this -> ocsp_uris ) ;
 }