static double calc_frame_boost ( const TWO_PASS * twopass , const FIRSTPASS_STATS * this_frame , double this_frame_mv_in_out ) {
 double frame_boost ;
 if ( this_frame -> intra_error > twopass -> gf_intra_err_min ) frame_boost = ( IIFACTOR * this_frame -> intra_error / DOUBLE_DIVIDE_CHECK ( this_frame -> coded_error ) ) ;
 else frame_boost = ( IIFACTOR * twopass -> gf_intra_err_min / DOUBLE_DIVIDE_CHECK ( this_frame -> coded_error ) ) ;
 if ( this_frame_mv_in_out > 0.0 ) frame_boost += frame_boost * ( this_frame_mv_in_out * 2.0 ) ;
 else frame_boost += frame_boost * ( this_frame_mv_in_out / 2.0 ) ;
 return MIN ( frame_boost , GF_RMAX ) ;
 }