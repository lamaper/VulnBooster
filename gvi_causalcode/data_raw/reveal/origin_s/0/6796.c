static int pubkey_get_npkey ( int algorithm ) {
 gcry_module_t pubkey ;
 int npkey = 0 ;
 REGISTER_DEFAULT_PUBKEYS ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 pubkey = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( pubkey ) {
 npkey = strlen ( ( ( gcry_pk_spec_t * ) pubkey -> spec ) -> elements_pkey ) ;
 _gcry_module_release ( pubkey ) ;
 }
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 return npkey ;
 }