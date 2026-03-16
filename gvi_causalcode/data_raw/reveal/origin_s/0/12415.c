static void compressed_sl_print ( netdissect_options * ndo , const u_char * chdr , const struct ip * ip , u_int length , int dir ) {
 register const u_char * cp = chdr ;
 register u_int flags , hlen ;
 flags = * cp ++ ;
 if ( flags & NEW_C ) {
 lastconn = * cp ++ ;
 ND_PRINT ( ( ndo , "ctcp %d" , lastconn ) ) ;
 }
 else ND_PRINT ( ( ndo , "ctcp *" ) ) ;
 cp += 2 ;
 switch ( flags & SPECIALS_MASK ) {
 case SPECIAL_I : ND_PRINT ( ( ndo , " *SA+%d" , lastlen [ dir ] [ lastconn ] ) ) ;
 break ;
 case SPECIAL_D : ND_PRINT ( ( ndo , " *S+%d" , lastlen [ dir ] [ lastconn ] ) ) ;
 break ;
 default : if ( flags & NEW_U ) cp = print_sl_change ( ndo , "U=" , cp ) ;
 if ( flags & NEW_W ) cp = print_sl_winchange ( ndo , cp ) ;
 if ( flags & NEW_A ) cp = print_sl_change ( ndo , "A+" , cp ) ;
 if ( flags & NEW_S ) cp = print_sl_change ( ndo , "S+" , cp ) ;
 break ;
 }
 if ( flags & NEW_I ) cp = print_sl_change ( ndo , "I+" , cp ) ;
 hlen = IP_HL ( ip ) ;
 hlen += TH_OFF ( ( const struct tcphdr * ) & ( ( const int32_t * ) ip ) [ hlen ] ) ;
 lastlen [ dir ] [ lastconn ] = length - ( hlen << 2 ) ;
 ND_PRINT ( ( ndo , " %d (%ld)" , lastlen [ dir ] [ lastconn ] , ( long ) ( cp - chdr ) ) ) ;
 }