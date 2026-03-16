METHOD ( certificate_t , equals , bool , private_x509_cert_t * this , certificate_t * other ) {
 chunk_t encoding ;
 bool equal ;
 if ( this == ( private_x509_cert_t * ) other ) {
 return TRUE ;
 }
 if ( other -> get_type ( other ) != CERT_X509 ) {
 return FALSE ;
 }
 if ( other -> equals == ( void * ) equals ) {
 return chunk_equals ( this -> encoding , ( ( private_x509_cert_t * ) other ) -> encoding ) ;
 }
 if ( ! other -> get_encoding ( other , CERT_ASN1_DER , & encoding ) ) {
 return FALSE ;
 }
 equal = chunk_equals ( this -> encoding , encoding ) ;
 free ( encoding . ptr ) ;
 return equal ;
 }