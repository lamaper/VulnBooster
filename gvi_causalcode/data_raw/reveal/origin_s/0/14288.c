static int gcry_pk_lookup_func_name ( void * spec , void * data ) {
 gcry_pk_spec_t * pubkey = ( gcry_pk_spec_t * ) spec ;
 char * name = ( char * ) data ;
 const char * * aliases = pubkey -> aliases ;
 int ret = stricmp ( name , pubkey -> name ) ;
 while ( ret && * aliases ) ret = stricmp ( name , * aliases ++ ) ;
 return ! ret ;
 }