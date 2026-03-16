static int input_stats ( TWO_PASS * p , FIRSTPASS_STATS * fps ) {
 if ( p -> stats_in >= p -> stats_in_end ) return EOF ;
 * fps = * p -> stats_in ;
 ++ p -> stats_in ;
 return 1 ;
 }