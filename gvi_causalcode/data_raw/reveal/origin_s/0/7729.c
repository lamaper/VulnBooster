gpg_error_t _gcry_pk_selftest ( int algo , int extended , selftest_report_func_t report ) {
 gcry_module_t module = NULL ;
 pk_extra_spec_t * extraspec = NULL ;
 gcry_err_code_t ec = 0 ;
 REGISTER_DEFAULT_PUBKEYS ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 module = _gcry_module_lookup_id ( pubkeys_registered , algo ) ;
 if ( module && ! ( module -> flags & FLAG_MODULE_DISABLED ) ) extraspec = module -> extraspec ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 if ( extraspec && extraspec -> selftest ) ec = extraspec -> selftest ( algo , extended , report ) ;
 else {
 ec = GPG_ERR_PUBKEY_ALGO ;
 if ( report ) report ( "pubkey" , algo , "module" , module && ! ( module -> flags & FLAG_MODULE_DISABLED ) ? "no selftest available" : module ? "algorithm disabled" : "algorithm not found" ) ;
 }
 if ( module ) {
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 _gcry_module_release ( module ) ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 }
 return gpg_error ( ec ) ;
 }