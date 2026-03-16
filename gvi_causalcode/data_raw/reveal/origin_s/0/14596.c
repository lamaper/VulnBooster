METHOD ( certificate_t , get_public_key , public_key_t * , private_x509_cert_t * this ) {
 this -> public_key -> get_ref ( this -> public_key ) ;
 return this -> public_key ;
 }