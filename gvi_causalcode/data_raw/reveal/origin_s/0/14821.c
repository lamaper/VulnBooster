METHOD ( x509_t , create_crl_uri_enumerator , enumerator_t * , private_x509_cert_t * this ) {
 return this -> crl_uris -> create_enumerator ( this -> crl_uris ) ;
 }