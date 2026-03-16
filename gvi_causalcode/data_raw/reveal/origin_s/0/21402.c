METHOD ( certificate_t , get_ref , certificate_t * , private_x509_cert_t * this ) {
 ref_get ( & this -> ref ) ;
 return & this -> public . interface . interface ;
 }