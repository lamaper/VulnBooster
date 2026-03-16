static gcry_err_code_t pubkey_check_secret_key ( int algorithm , gcry_mpi_t * skey ) {
 gcry_err_code_t err = GPG_ERR_PUBKEY_ALGO ;
 gcry_module_t pubkey ;
 REGISTER_DEFAULT_PUBKEYS ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 pubkey = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( pubkey ) {
 err = ( ( gcry_pk_spec_t * ) pubkey -> spec ) -> check_secret_key ( algorithm , skey ) ;
 _gcry_module_release ( pubkey ) ;
 }
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 return err ;
 }