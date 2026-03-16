METHOD ( x509_t , create_cert_policy_enumerator , enumerator_t * , private_x509_cert_t * this ) {
 return this -> cert_policies -> create_enumerator ( this -> cert_policies ) ;
 }