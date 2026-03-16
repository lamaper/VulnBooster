static gcry_err_code_t pubkey_decrypt ( int algorithm , gcry_mpi_t * result , gcry_mpi_t * data , gcry_mpi_t * skey , int flags ) {
 gcry_pk_spec_t * pubkey ;
 gcry_module_t module ;
 gcry_err_code_t rc ;
 int i ;
 * result = NULL ;
 if ( DBG_CIPHER && ! fips_mode ( ) ) {
 log_debug ( "pubkey_decrypt: algo=%d\n" , algorithm ) ;
 for ( i = 0 ;
 i < pubkey_get_nskey ( algorithm ) ;
 i ++ ) log_mpidump ( " skey" , skey [ i ] ) ;
 for ( i = 0 ;
 i < pubkey_get_nenc ( algorithm ) ;
 i ++ ) log_mpidump ( " data" , data [ i ] ) ;
 }
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 module = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( module ) {
 pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 rc = pubkey -> decrypt ( algorithm , result , data , skey , flags ) ;
 _gcry_module_release ( module ) ;
 goto ready ;
 }
 rc = GPG_ERR_PUBKEY_ALGO ;
 ready : ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 if ( ! rc && DBG_CIPHER && ! fips_mode ( ) ) log_mpidump ( " plain" , * result ) ;
 return rc ;
 }