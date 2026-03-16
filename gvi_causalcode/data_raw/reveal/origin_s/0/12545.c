gcry_error_t gcry_pk_algo_info ( int algorithm , int what , void * buffer , size_t * nbytes ) {
 gcry_err_code_t err = GPG_ERR_NO_ERROR ;
 switch ( what ) {
 case GCRYCTL_TEST_ALGO : {
 int use = nbytes ? * nbytes : 0 ;
 if ( buffer ) err = GPG_ERR_INV_ARG ;
 else if ( check_pubkey_algo ( algorithm , use ) ) err = GPG_ERR_PUBKEY_ALGO ;
 break ;
 }
 case GCRYCTL_GET_ALGO_USAGE : {
 gcry_module_t pubkey ;
 int use = 0 ;
 REGISTER_DEFAULT_PUBKEYS ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 pubkey = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( pubkey ) {
 use = ( ( gcry_pk_spec_t * ) pubkey -> spec ) -> use ;
 _gcry_module_release ( pubkey ) ;
 }
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 * nbytes = use ;
 break ;
 }
 case GCRYCTL_GET_ALGO_NPKEY : {
 int npkey = pubkey_get_npkey ( algorithm ) ;
 * nbytes = npkey ;
 break ;
 }
 case GCRYCTL_GET_ALGO_NSKEY : {
 int nskey = pubkey_get_nskey ( algorithm ) ;
 * nbytes = nskey ;
 break ;
 }
 case GCRYCTL_GET_ALGO_NSIGN : {
 int nsign = pubkey_get_nsig ( algorithm ) ;
 * nbytes = nsign ;
 break ;
 }
 case GCRYCTL_GET_ALGO_NENCR : {
 int nencr = pubkey_get_nenc ( algorithm ) ;
 * nbytes = nencr ;
 break ;
 }
 default : err = GPG_ERR_INV_OP ;
 }
 return gcry_error ( err ) ;
 }