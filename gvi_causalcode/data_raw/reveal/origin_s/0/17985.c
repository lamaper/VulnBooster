static void crl_uri_destroy ( x509_cdp_t * this ) {
 free ( this -> uri ) ;
 DESTROY_IF ( this -> issuer ) ;
 free ( this ) ;
 }