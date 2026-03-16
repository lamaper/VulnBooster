void vp9_adapt_coef_probs ( VP9_COMMON * cm ) {
 TX_SIZE t ;
 unsigned int count_sat , update_factor ;
 if ( frame_is_intra_only ( cm ) ) {
 update_factor = COEF_MAX_UPDATE_FACTOR_KEY ;
 count_sat = COEF_COUNT_SAT_KEY ;
 }
 else if ( cm -> last_frame_type == KEY_FRAME ) {
 update_factor = COEF_MAX_UPDATE_FACTOR_AFTER_KEY ;
 count_sat = COEF_COUNT_SAT_AFTER_KEY ;
 }
 else {
 update_factor = COEF_MAX_UPDATE_FACTOR ;
 count_sat = COEF_COUNT_SAT ;
 }
 for ( t = TX_4X4 ;
 t <= TX_32X32 ;
 t ++ ) adapt_coef_probs ( cm , t , count_sat , update_factor ) ;
 }