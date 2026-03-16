static void disable_pubkey_algo ( int algorithm ) {
 gcry_module_t pubkey ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 pubkey = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( pubkey ) {
 if ( ! ( pubkey -> flags & FLAG_MODULE_DISABLED ) ) pubkey -> flags |= FLAG_MODULE_DISABLED ;
 _gcry_module_release ( pubkey ) ;
 }
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 }