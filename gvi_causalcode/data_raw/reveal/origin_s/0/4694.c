static int codebook_sanity_check_for_rate_quarter ( const uint8_t * cbgain ) {
 int i , diff , prev_diff = 0 ;
 for ( i = 1 ;
 i < 5 ;
 i ++ ) {
 diff = cbgain [ i ] - cbgain [ i - 1 ] ;
 if ( FFABS ( diff ) > 10 ) return - 1 ;
 else if ( FFABS ( diff - prev_diff ) > 12 ) return - 1 ;
 prev_diff = diff ;
 }
 return 0 ;
 }