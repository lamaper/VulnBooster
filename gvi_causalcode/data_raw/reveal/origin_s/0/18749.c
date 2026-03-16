METHOD ( certificate_t , has_issuer , id_match_t , private_x509_cert_t * this , identification_t * issuer ) {
 return this -> issuer -> matches ( this -> issuer , issuer ) ;
 }