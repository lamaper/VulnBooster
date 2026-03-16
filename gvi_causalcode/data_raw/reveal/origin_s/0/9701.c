static gcry_err_code_t pubkey_sign ( int algorithm , gcry_mpi_t * resarr , gcry_mpi_t data , gcry_mpi_t * skey , struct pk_encoding_ctx * ctx ) {
 gcry_pk_spec_t * pubkey ;
 gcry_module_t module ;
 gcry_err_code_t rc ;
 int i ;
 if ( DBG_CIPHER && ! fips_mode ( ) ) {
 log_debug ( "pubkey_sign: algo=%d\n" , algorithm ) ;
 for ( i = 0 ;
 i < pubkey_get_nskey ( algorithm ) ;
 i ++ ) log_mpidump ( " skey" , skey [ i ] ) ;
 log_mpidump ( " data" , data ) ;
 }
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 module = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( module ) {
 pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 rc = pubkey -> sign ( algorithm , resarr , data , skey , ctx -> flags , ctx -> hash_algo ) ;
 _gcry_module_release ( module ) ;
 goto ready ;
 }
 rc = GPG_ERR_PUBKEY_ALGO ;
 ready : ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 if ( ! rc && DBG_CIPHER && ! fips_mode ( ) ) for ( i = 0 ;
 i < pubkey_get_nsig ( algorithm ) ;
 i ++ ) log_mpidump ( " sig" , resarr [ i ] ) ;
 return rc ;
 }