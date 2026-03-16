METHOD ( x509_t , create_ipAddrBlock_enumerator , enumerator_t * , private_x509_cert_t * this ) {
 return this -> ipAddrBlocks -> create_enumerator ( this -> ipAddrBlocks ) ;
 }