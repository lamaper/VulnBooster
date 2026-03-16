static int detect_transition_to_still ( const TWO_PASS * twopass , int frame_interval , int still_interval , double loop_decay_rate , double last_decay_rate ) {
 if ( frame_interval > MIN_GF_INTERVAL && loop_decay_rate >= 0.999 && last_decay_rate < 0.9 ) {
 int j ;
 for ( j = 0 ;
 j < still_interval ;
 ++ j ) {
 const FIRSTPASS_STATS * stats = & twopass -> stats_in [ j ] ;
 if ( stats >= twopass -> stats_in_end ) break ;
 if ( stats -> pcnt_inter - stats -> pcnt_motion < 0.999 ) break ;
 }
 return j == still_interval ;
 }
 return 0 ;
 }