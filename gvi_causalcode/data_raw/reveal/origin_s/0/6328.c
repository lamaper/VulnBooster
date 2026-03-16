static gcry_err_code_t pubkey_verify ( int algorithm , gcry_mpi_t hash , gcry_mpi_t * data , gcry_mpi_t * pkey , struct pk_encoding_ctx * ctx ) {
 gcry_pk_spec_t * pubkey ;
 gcry_module_t module ;
 gcry_err_code_t rc ;
 int i ;
 if ( DBG_CIPHER && ! fips_mode ( ) ) {
 log_debug ( "pubkey_verify: algo=%d\n" , algorithm ) ;
 for ( i = 0 ;
 i < pubkey_get_npkey ( algorithm ) ;
 i ++ ) log_mpidump ( " pkey" , pkey [ i ] ) ;
 for ( i = 0 ;
 i < pubkey_get_nsig ( algorithm ) ;
 i ++ ) log_mpidump ( " sig" , data [ i ] ) ;
 log_mpidump ( " hash" , hash ) ;
 }
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 module = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( module ) {
 pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 rc = pubkey -> verify ( algorithm , hash , data , pkey , ctx -> verify_cmp , ctx , ctx -> flags , ctx -> hash_algo ) ;
 _gcry_module_release ( module ) ;
 goto ready ;
 }
 rc = GPG_ERR_PUBKEY_ALGO ;
 ready : ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 return rc ;
 }