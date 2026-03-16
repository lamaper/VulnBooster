static gcry_err_code_t pubkey_generate ( int algorithm , unsigned int nbits , unsigned long use_e , gcry_sexp_t genparms , gcry_mpi_t * skey , gcry_mpi_t * * retfactors , gcry_sexp_t * r_extrainfo ) {
 gcry_err_code_t ec = GPG_ERR_PUBKEY_ALGO ;
 gcry_module_t pubkey ;
 REGISTER_DEFAULT_PUBKEYS ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 pubkey = _gcry_module_lookup_id ( pubkeys_registered , algorithm ) ;
 if ( pubkey ) {
 pk_extra_spec_t * extraspec = pubkey -> extraspec ;
 if ( extraspec && extraspec -> ext_generate ) {
 ec = extraspec -> ext_generate ( algorithm , nbits , use_e , genparms , skey , retfactors , r_extrainfo ) ;
 }
 else {
 ec = ( ( gcry_pk_spec_t * ) pubkey -> spec ) -> generate ( algorithm , nbits , use_e , skey , retfactors ) ;
 }
 _gcry_module_release ( pubkey ) ;
 }
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 return ec ;
 }