METHOD ( certificate_t , get_validity , bool , private_x509_cert_t * this , time_t * when , time_t * not_before , time_t * not_after ) {
 time_t t = when ? * when : time ( NULL ) ;
 if ( not_before ) {
 * not_before = this -> notBefore ;
 }
 if ( not_after ) {
 * not_after = this -> notAfter ;
 }
 return ( t >= this -> notBefore && t <= this -> notAfter ) ;
 }