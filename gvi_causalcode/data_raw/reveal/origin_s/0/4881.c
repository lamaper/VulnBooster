static u_short create_scan_states ( char * text , u_short token , follby followedby , u_short prev_state ) {
 u_short my_state ;
 u_short return_state ;
 u_short prev_char_s ;
 u_short curr_char_s ;
 return_state = prev_state ;
 curr_char_s = prev_state ;
 prev_char_s = 0 ;
 while ( curr_char_s && ( text [ 0 ] < sst [ curr_char_s ] . ch ) ) {
 prev_char_s = curr_char_s ;
 curr_char_s = sst [ curr_char_s ] . other_next_s ;
 }
 if ( curr_char_s && ( text [ 0 ] == sst [ curr_char_s ] . ch ) ) {
 my_state = curr_char_s ;
 if ( '\0' == text [ 1 ] ) {
 fprintf ( stderr , "Duplicate entries for keyword '%s' in" " keyword_gen.c ntp_keywords[].\n" , current_keyword ) ;
 exit ( 2 ) ;
 }
 }
 else {
 do my_state = sst_highwater ++ ;
 while ( my_state < COUNTOF ( sst ) && sst [ my_state ] . finishes_token ) ;
 if ( my_state >= COUNTOF ( sst ) ) {
 fprintf ( stderr , "fatal, keyword scanner state array " "sst[%d] is too small, modify\n" "keyword-gen.c to increase.\n" , ( int ) COUNTOF ( sst ) ) ;
 exit ( 3 ) ;
 }
 sst [ my_state ] . ch = text [ 0 ] ;
 sst [ my_state ] . other_next_s = curr_char_s ;
 sst [ my_state ] . followedby = FOLLBY_NON_ACCEPTING ;
 if ( prev_char_s ) sst [ prev_char_s ] . other_next_s = my_state ;
 else return_state = my_state ;
 }
 if ( '\0' == text [ 1 ] ) {
 sst [ my_state ] . finishes_token = ( u_short ) token ;
 sst [ my_state ] . followedby = ( char ) followedby ;
 if ( sst [ token ] . finishes_token != ( u_short ) token ) {
 fprintf ( stderr , "fatal, sst[%d] not reserved for %s.\n" , token , symbname ( token ) ) ;
 exit ( 6 ) ;
 }
 if ( my_state != token ) {
 sst [ token ] = sst [ my_state ] ;
 ZERO ( sst [ my_state ] ) ;
 do sst_highwater -- ;
 while ( sst [ sst_highwater ] . finishes_token ) ;
 my_state = token ;
 if ( prev_char_s ) sst [ prev_char_s ] . other_next_s = my_state ;
 else return_state = my_state ;
 }
 }
 else sst [ my_state ] . match_next_s = create_scan_states ( & text [ 1 ] , token , followedby , sst [ my_state ] . match_next_s ) ;
 return return_state ;
 }