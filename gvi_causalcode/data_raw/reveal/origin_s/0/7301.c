gcry_error_t _gcry_pk_register ( gcry_pk_spec_t * pubkey , pk_extra_spec_t * extraspec , unsigned int * algorithm_id , gcry_module_t * module ) {
 gcry_err_code_t err = GPG_ERR_NO_ERROR ;
 gcry_module_t mod ;
 if ( fips_mode ( ) ) return gpg_error ( GPG_ERR_NOT_SUPPORTED ) ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 err = _gcry_module_add ( & pubkeys_registered , 0 , ( void * ) pubkey , ( void * ) ( extraspec ? extraspec : & dummy_extra_spec ) , & mod ) ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 if ( ! err ) {
 * module = mod ;
 * algorithm_id = mod -> mod_id ;
 }
 return err ;
 }