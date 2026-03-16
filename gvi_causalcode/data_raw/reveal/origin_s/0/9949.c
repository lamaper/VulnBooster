static double get_sr_decay_rate ( const VP9_COMMON * cm , const FIRSTPASS_STATS * frame ) {
 double sr_diff = ( frame -> sr_coded_error - frame -> coded_error ) / cm -> MBs ;
 double sr_decay = 1.0 ;
 const double motion_amplitude_factor = frame -> pcnt_motion * ( ( frame -> mvc_abs + frame -> mvr_abs ) / 2 ) ;
 const double pcnt_intra = 100 * ( 1.0 - frame -> pcnt_inter ) ;
 if ( ( sr_diff > LOW_SR_DIFF_TRHESH ) ) {
 sr_diff = MIN ( sr_diff , SR_DIFF_MAX ) ;
 sr_decay = 1.0 - ( SR_DIFF_PART * sr_diff ) - ( MOTION_AMP_PART * motion_amplitude_factor ) - ( INTRA_PART * pcnt_intra ) ;
 }
 return MAX ( sr_decay , MIN ( DEFAULT_DECAY_LIMIT , frame -> pcnt_inter ) ) ;
 }