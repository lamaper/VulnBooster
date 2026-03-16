static void cert_policy_destroy ( x509_cert_policy_t * this ) {
 free ( this -> oid . ptr ) ;
 free ( this -> cps_uri ) ;
 free ( this -> unotice_text ) ;
 free ( this ) ;
 }