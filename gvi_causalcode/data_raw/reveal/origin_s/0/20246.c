static int detect_flash ( const TWO_PASS * twopass , int offset ) {
 const FIRSTPASS_STATS * const next_frame = read_frame_stats ( twopass , offset ) ;
 return next_frame != NULL && next_frame -> pcnt_second_ref > next_frame -> pcnt_inter && next_frame -> pcnt_second_ref >= 0.5 ;
 }