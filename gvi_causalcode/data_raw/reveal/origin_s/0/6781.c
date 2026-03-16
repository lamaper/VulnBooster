const char * gcry_pk_algo_name ( int algorithm ) {
 gcry_module_t pubkey ;
 const char * name ;
 REGISTER_DEFAULT_PUBKEYS ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 pubkey = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( pubkey ) {
 name = ( ( gcry_pk_spec_t * ) pubkey -> spec ) -> name ;
 _gcry_module_release ( pubkey ) ;
 }
 else name = "?" ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 return name ;
 }