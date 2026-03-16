int gcry_pk_map_name ( const char * string ) {
 gcry_module_t pubkey ;
 int algorithm = 0 ;
 if ( ! string ) return 0 ;
 REGISTER_DEFAULT_PUBKEYS ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 pubkey = gcry_pk_lookup_name ( string ) ;
 if ( pubkey ) {
 algorithm = pubkey -> mod_id ;
 _gcry_module_release ( pubkey ) ;
 }
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 return algorithm ;
 }