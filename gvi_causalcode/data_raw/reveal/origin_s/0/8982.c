unsigned int gcry_pk_get_nbits ( gcry_sexp_t key ) {
 gcry_module_t module = NULL ;
 gcry_pk_spec_t * pubkey ;
 gcry_mpi_t * keyarr = NULL ;
 unsigned int nbits = 0 ;
 gcry_err_code_t rc ;
 REGISTER_DEFAULT_PUBKEYS ;
 rc = sexp_to_key ( key , 0 , 0 , NULL , & keyarr , & module , NULL ) ;
 if ( rc == GPG_ERR_INV_OBJ ) rc = sexp_to_key ( key , 1 , 0 , NULL , & keyarr , & module , NULL ) ;
 if ( rc ) return 0 ;
 pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 nbits = ( * pubkey -> get_nbits ) ( module -> mod_id , keyarr ) ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 _gcry_module_release ( module ) ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 release_mpi_array ( keyarr ) ;
 gcry_free ( keyarr ) ;
 return nbits ;
 }