static gcry_err_code_t pubkey_encrypt ( int algorithm , gcry_mpi_t * resarr , gcry_mpi_t data , gcry_mpi_t * pkey , int flags ) {
 gcry_pk_spec_t * pubkey ;
 gcry_module_t module ;
 gcry_err_code_t rc ;
 int i ;
 if ( DBG_CIPHER && ! fips_mode ( ) ) {
 log_debug ( "pubkey_encrypt: algo=%d\n" , algorithm ) ;
 for ( i = 0 ;
 i < pubkey_get_npkey ( algorithm ) ;
 i ++ ) log_mpidump ( " pkey" , pkey [ i ] ) ;
 log_mpidump ( " data" , data ) ;
 }
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 module = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( module ) {
 pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 rc = pubkey -> encrypt ( algorithm , resarr , data , pkey , flags ) ;
 _gcry_module_release ( module ) ;
 goto ready ;
 }
 rc = GPG_ERR_PUBKEY_ALGO ;
 ready : ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 if ( ! rc && DBG_CIPHER && ! fips_mode ( ) ) {
 for ( i = 0 ;
 i < pubkey_get_nenc ( algorithm ) ;
 i ++ ) log_mpidump ( " encr" , resarr [ i ] ) ;
 }
 return rc ;
 }