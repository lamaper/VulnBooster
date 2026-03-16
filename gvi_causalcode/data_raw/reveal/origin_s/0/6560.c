static void generate_fsm ( void ) {
 char rprefix [ MAX_TOK_LEN + 1 ] ;
 char prefix [ MAX_TOK_LEN + 1 ] ;
 char token_id_comment [ 16 + MAX_TOK_LEN + 1 ] ;
 size_t prefix_len ;
 char * p ;
 char * r ;
 u_short initial_state ;
 u_short this_state ;
 u_short state ;
 u_short i ;
 u_short token ;
 qsort ( ntp_keywords , COUNTOF ( ntp_keywords ) , sizeof ( ntp_keywords [ 0 ] ) , compare_key_tok_text ) ;
 for ( i = 0 ;
 i < COUNTOF ( ntp_keywords ) ;
 i ++ ) {
 token = ntp_keywords [ i ] . token ;
 if ( 1 > token || token >= COUNTOF ( sst ) ) {
 fprintf ( stderr , "keyword-gen sst[%u] too small " "for keyword '%s' id %d\n" , ( int ) COUNTOF ( sst ) , ntp_keywords [ i ] . key , token ) ;
 exit ( 4 ) ;
 }
 sst [ token ] . finishes_token = token ;
 }
 initial_state = create_keyword_scanner ( ) ;
 fprintf ( stderr , "%d keywords consumed %d states of %d max.\n" , ( int ) COUNTOF ( ntp_keywords ) , sst_highwater - 1 , ( int ) COUNTOF ( sst ) - 1 ) ;
 printf ( "#define SCANNER_INIT_S %d\n\n" , initial_state ) ;
 printf ( "const scan_state sst[%d] = {
\n" "/*SS_T( ch,\tf-by, match, other ),\t\t\t\t */\n" " 0,\t\t\t\t /* %5d %-17s */\n" , sst_highwater , 0 , "" ) ;
 for ( i = 1 ;
 i < sst_highwater ;
 i ++ ) {
 if ( sst [ i ] . followedby & ~ 0x3 ) {
 fprintf ( stderr , "keyword-gen internal error " "sst[%d].followedby %d too big\n" , i , sst [ i ] . followedby ) ;
 exit ( 7 ) ;
 }
 if ( sst_highwater <= sst [ i ] . match_next_s || sst [ i ] . match_next_s & ~ 0x7ff ) {
 fprintf ( stderr , "keyword-gen internal error " "sst[%d].match_next_s %d too big\n" , i , sst [ i ] . match_next_s ) ;
 exit ( 8 ) ;
 }
 if ( sst_highwater <= sst [ i ] . other_next_s || sst [ i ] . other_next_s & ~ 0x7ff ) {
 fprintf ( stderr , "keyword-gen internal error " "sst[%d].other_next_s %d too big\n" , i , sst [ i ] . other_next_s ) ;
 exit ( 9 ) ;
 }
 if ( sst [ i ] . finishes_token ) {
 snprintf ( token_id_comment , sizeof ( token_id_comment ) , "%5d %-17s" , i , symbname ( sst [ i ] . finishes_token ) ) ;
 if ( i != sst [ i ] . finishes_token ) {
 fprintf ( stderr , "keyword-gen internal error " "entry %d finishes token %d\n" , i , sst [ i ] . finishes_token ) ;
 exit ( 5 ) ;
 }
 }
 else {
 prefix_len = 0 ;
 this_state = i ;
 do {
 for ( state = 1 ;
 state < sst_highwater ;
 state ++ ) if ( sst [ state ] . other_next_s == this_state ) {
 this_state = state ;
 break ;
 }
 else if ( sst [ state ] . match_next_s == this_state ) {
 this_state = state ;
 rprefix [ prefix_len ] = sst [ state ] . ch ;
 prefix_len ++ ;
 break ;
 }
 }
 while ( this_state != initial_state ) ;
 if ( prefix_len ) {
 p = prefix + prefix_len ;
 r = rprefix ;
 while ( r < rprefix + prefix_len ) * -- p = * r ++ ;
 }
 prefix [ prefix_len ] = '\0' ;
 snprintf ( token_id_comment , sizeof ( token_id_comment ) , "%5d %-17s" , i , ( initial_state == i ) ? "[initial state]" : prefix ) ;
 }
 printf ( " S_ST( '%c',\t%d, %5u, %5u )%s /* %s */\n" , sst [ i ] . ch , sst [ i ] . followedby , sst [ i ] . match_next_s , sst [ i ] . other_next_s , ( i + 1 < sst_highwater ) ? "," : " " , token_id_comment ) ;
 }
 printf ( "}
;
\n\n" ) ;
 }