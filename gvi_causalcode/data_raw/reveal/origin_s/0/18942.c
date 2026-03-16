const char * _gcry_pk_aliased_algo_name ( int algorithm ) {
 const char * name = NULL ;
 gcry_module_t module ;
 REGISTER_DEFAULT_PUBKEYS ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 module = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( module ) {
 gcry_pk_spec_t * pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 name = pubkey -> aliases ? * pubkey -> aliases : NULL ;
 if ( ! name || ! * name ) name = pubkey -> name ;
 _gcry_module_release ( module ) ;
 }
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 return name ;
 }