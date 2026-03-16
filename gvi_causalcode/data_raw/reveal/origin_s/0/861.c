static const u_char * print_sl_change ( netdissect_options * ndo , const char * str , register const u_char * cp ) {
 register u_int i ;
 if ( ( i = * cp ++ ) == 0 ) {
 i = EXTRACT_16BITS ( cp ) ;
 cp += 2 ;
 }
 ND_PRINT ( ( ndo , " %s%d" , str , i ) ) ;
 return ( cp ) ;
 }