static void lookup_doit ( void * a ) {
 struct lookup_args * args = ( struct lookup_args * ) a ;
 const ElfW ( Sym ) * ref = NULL ;
 args -> result = NULL ;
 lookup_t l = _dl_lookup_symbol_x ( args -> name , args -> map , & ref , args -> map -> l_local_scope , NULL , 0 , DL_LOOKUP_RETURN_NEWEST , NULL ) ;
 if ( ref != NULL ) args -> result = DL_SYMBOL_ADDRESS ( l , ref ) ;
 }