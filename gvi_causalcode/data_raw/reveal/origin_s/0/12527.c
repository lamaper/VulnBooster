unsigned char * gcry_pk_get_keygrip ( gcry_sexp_t key , unsigned char * array ) {
 gcry_sexp_t list = NULL , l2 = NULL ;
 gcry_pk_spec_t * pubkey = NULL ;
 gcry_module_t module = NULL ;
 pk_extra_spec_t * extraspec ;
 const char * s ;
 char * name = NULL ;
 int idx ;
 const char * elems ;
 gcry_md_hd_t md = NULL ;
 int okay = 0 ;
 REGISTER_DEFAULT_PUBKEYS ;
 list = gcry_sexp_find_token ( key , "public-key" , 0 ) ;
 if ( ! list ) list = gcry_sexp_find_token ( key , "private-key" , 0 ) ;
 if ( ! list ) list = gcry_sexp_find_token ( key , "protected-private-key" , 0 ) ;
 if ( ! list ) list = gcry_sexp_find_token ( key , "shadowed-private-key" , 0 ) ;
 if ( ! list ) return NULL ;
 l2 = gcry_sexp_cadr ( list ) ;
 gcry_sexp_release ( list ) ;
 list = l2 ;
 l2 = NULL ;
 name = _gcry_sexp_nth_string ( list , 0 ) ;
 if ( ! name ) goto fail ;
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 module = gcry_pk_lookup_name ( name ) ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 if ( ! module ) goto fail ;
 pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 extraspec = module -> extraspec ;
 elems = pubkey -> elements_grip ;
 if ( ! elems ) goto fail ;
 if ( gcry_md_open ( & md , GCRY_MD_SHA1 , 0 ) ) goto fail ;
 if ( extraspec && extraspec -> comp_keygrip ) {
 if ( extraspec -> comp_keygrip ( md , list ) ) goto fail ;
 }
 else {
 for ( idx = 0 , s = elems ;
 * s ;
 s ++ , idx ++ ) {
 const char * data ;
 size_t datalen ;
 char buf [ 30 ] ;
 l2 = gcry_sexp_find_token ( list , s , 1 ) ;
 if ( ! l2 ) goto fail ;
 data = gcry_sexp_nth_data ( l2 , 1 , & datalen ) ;
 if ( ! data ) goto fail ;
 snprintf ( buf , sizeof buf , "(1:%c%u:" , * s , ( unsigned int ) datalen ) ;
 gcry_md_write ( md , buf , strlen ( buf ) ) ;
 gcry_md_write ( md , data , datalen ) ;
 gcry_sexp_release ( l2 ) ;
 l2 = NULL ;
 gcry_md_write ( md , ")" , 1 ) ;
 }
 }
 if ( ! array ) {
 array = gcry_malloc ( 20 ) ;
 if ( ! array ) goto fail ;
 }
 memcpy ( array , gcry_md_read ( md , GCRY_MD_SHA1 ) , 20 ) ;
 okay = 1 ;
 fail : gcry_free ( name ) ;
 gcry_sexp_release ( l2 ) ;
 gcry_md_close ( md ) ;
 gcry_sexp_release ( list ) ;
 return okay ? array : NULL ;
 }