void _gcry_pk_unregister ( gcry_module_t module ) {
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 _gcry_module_release ( module ) ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 }