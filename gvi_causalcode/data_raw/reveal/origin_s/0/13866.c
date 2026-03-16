static int convert_to_hex ( const unsigned char * src , size_t len , char * dest ) {
 int i ;
 if ( dest ) {
 * dest ++ = '#' ;
 for ( i = 0 ;
 i < len ;
 i ++ , dest += 2 ) sprintf ( dest , "%02X" , src [ i ] ) ;
 * dest ++ = '#' ;
 }
 return len * 2 + 2 ;
 }