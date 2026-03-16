static int pubkey_get_nskey ( int algorithm ) {
 gcry_module_t pubkey ;
 int nskey = 0 ;
 REGISTER_DEFAULT_PUBKEYS ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 pubkey = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( pubkey ) {
 nskey = strlen ( ( ( gcry_pk_spec_t * ) pubkey -> spec ) -> elements_skey ) ;
 _gcry_module_release ( pubkey ) ;
 }
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 return nskey ;
 }