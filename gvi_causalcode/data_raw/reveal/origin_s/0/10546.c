static double get_prediction_decay_rate ( const VP9_COMMON * cm , const FIRSTPASS_STATS * next_frame ) {
 const double sr_decay_rate = get_sr_decay_rate ( cm , next_frame ) ;
 const double zero_motion_factor = ( 0.95 * pow ( ( next_frame -> pcnt_inter - next_frame -> pcnt_motion ) , ZM_POWER_FACTOR ) ) ;
 return MAX ( zero_motion_factor , ( sr_decay_rate + ( ( 1.0 - sr_decay_rate ) * zero_motion_factor ) ) ) ;
 }