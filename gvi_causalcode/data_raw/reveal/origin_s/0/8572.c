static double get_zero_motion_factor ( const VP9_COMMON * cm , const FIRSTPASS_STATS * frame ) {
 const double zero_motion_pct = frame -> pcnt_inter - frame -> pcnt_motion ;
 double sr_decay = get_sr_decay_rate ( cm , frame ) ;
 return MIN ( sr_decay , zero_motion_pct ) ;
 }