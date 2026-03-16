static gcry_err_code_t check_pubkey_algo ( int algorithm , unsigned use ) {
 gcry_err_code_t err = GPG_ERR_NO_ERROR ;
 gcry_pk_spec_t * pubkey ;
 gcry_module_t module ;
 REGISTER_DEFAULT_PUBKEYS ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 module = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( module ) {
 pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 if ( ( ( use & GCRY_PK_USAGE_SIGN ) && ( ! ( pubkey -> use & GCRY_PK_USAGE_SIGN ) ) ) || ( ( use & GCRY_PK_USAGE_ENCR ) && ( ! ( pubkey -> use & GCRY_PK_USAGE_ENCR ) ) ) ) err = GPG_ERR_WRONG_PUBKEY_ALGO ;
 else if ( module -> flags & FLAG_MODULE_DISABLED ) err = GPG_ERR_PUBKEY_ALGO ;
 _gcry_module_release ( module ) ;
 }
 else err = GPG_ERR_PUBKEY_ALGO ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 return err ;
 }