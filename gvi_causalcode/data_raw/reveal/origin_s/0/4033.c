static void generate_token_text ( void ) {
 u_short lowest_id ;
 u_short highest_id ;
 u_short id_count ;
 u_short id ;
 u_short i ;
 qsort ( ntp_keywords , COUNTOF ( ntp_keywords ) , sizeof ( ntp_keywords [ 0 ] ) , compare_key_tok_id ) ;
 lowest_id = ntp_keywords [ 0 ] . token ;
 highest_id = ntp_keywords [ COUNTOF ( ntp_keywords ) - 1 ] . token ;
 id_count = highest_id - lowest_id + 1 ;
 printf ( "#define LOWEST_KEYWORD_ID %d\n\n" , lowest_id ) ;
 printf ( "const char * const keyword_text[%d] = {
" , id_count ) ;
 id = lowest_id ;
 i = 0 ;
 while ( i < COUNTOF ( ntp_keywords ) ) {
 while ( id < ntp_keywords [ i ] . token ) {
 printf ( ",\n\t/* %-5d %5d %20s */\tNULL" , id - lowest_id , id , symbname ( id ) ) ;
 id ++ ;
 }
 if ( i > 0 ) printf ( "," ) ;
 printf ( "\n\t/* %-5d %5d %20s */\t\"%s\"" , id - lowest_id , id , symbname ( id ) , ntp_keywords [ i ] . key ) ;
 i ++ ;
 id ++ ;
 }
 printf ( "\n}
;
\n\n" ) ;
 }