int ztoken_get_scanner_option ( const ref * psref , int options , const char * * pname ) {
 const named_scanner_option_t * pnso ;
 for ( pnso = named_options + countof ( named_options ) ;
 pnso -- != named_options ;
 ) {
 if ( ! bytes_compare ( ( const byte * ) pnso -> pname , strlen ( pnso -> pname ) , psref -> value . const_bytes , r_size ( psref ) ) ) {
 * pname = pnso -> pname ;
 return ( options & pnso -> option ? 1 : 0 ) ;
 }
 }
 return - 1 ;
 }