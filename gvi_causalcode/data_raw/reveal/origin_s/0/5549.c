static void policy_mapping_destroy ( x509_policy_mapping_t * mapping ) {
 free ( mapping -> issuer . ptr ) ;
 free ( mapping -> subject . ptr ) ;
 free ( mapping ) ;
 }