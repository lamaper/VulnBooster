static double get_zero_motion_factor ( const FIRSTPASS_STATS * frame ) {
 const double sr_ratio = frame -> coded_error / DOUBLE_DIVIDE_CHECK ( frame -> sr_coded_error ) ;
 const double zero_motion_pct = frame -> pcnt_inter - frame -> pcnt_motion ;
 return MIN ( sr_ratio , zero_motion_pct ) ;
 }