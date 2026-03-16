METHOD ( x509_t , create_policy_mapping_enumerator , enumerator_t * , private_x509_cert_t * this ) {
 return this -> policy_mappings -> create_enumerator ( this -> policy_mappings ) ;
 }