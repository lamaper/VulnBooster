static void accumulate_frame_motion_stats ( const FIRSTPASS_STATS * stats , double * mv_in_out , double * mv_in_out_accumulator , double * abs_mv_in_out_accumulator , double * mv_ratio_accumulator ) {
 const double pct = stats -> pcnt_motion ;
 * mv_in_out = stats -> mv_in_out_count * pct ;
 * mv_in_out_accumulator += * mv_in_out ;
 * abs_mv_in_out_accumulator += fabs ( * mv_in_out ) ;
 if ( pct > 0.05 ) {
 const double mvr_ratio = fabs ( stats -> mvr_abs ) / DOUBLE_DIVIDE_CHECK ( fabs ( stats -> MVr ) ) ;
 const double mvc_ratio = fabs ( stats -> mvc_abs ) / DOUBLE_DIVIDE_CHECK ( fabs ( stats -> MVc ) ) ;
 * mv_ratio_accumulator += pct * ( mvr_ratio < stats -> mvr_abs ? mvr_ratio : stats -> mvr_abs ) ;
 * mv_ratio_accumulator += pct * ( mvc_ratio < stats -> mvc_abs ? mvc_ratio : stats -> mvc_abs ) ;
 }
 }