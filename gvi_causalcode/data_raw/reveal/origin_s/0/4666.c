static gcry_module_t gcry_pk_lookup_name ( const char * name ) {
 gcry_module_t pubkey ;
 pubkey = _gcry_module_lookup ( pubkeys_registered , ( void * ) name , gcry_pk_lookup_func_name ) ;
 return pubkey ;
 }