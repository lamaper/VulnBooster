static const u_char * print_sl_winchange ( netdissect_options * ndo , register const u_char * cp ) {
 register short i ;
 if ( ( i = * cp ++ ) == 0 ) {
 i = EXTRACT_16BITS ( cp ) ;
 cp += 2 ;
 }
 if ( i >= 0 ) ND_PRINT ( ( ndo , " W+%d" , i ) ) ;
 else ND_PRINT ( ( ndo , " W%d" , i ) ) ;
 return ( cp ) ;
 }