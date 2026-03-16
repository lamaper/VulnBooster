static double get_prediction_decay_rate ( const VP9_COMMON * cm , const FIRSTPASS_STATS * next_frame ) {
 const double mb_sr_err_diff = ( next_frame -> sr_coded_error - next_frame -> coded_error ) / cm -> MBs ;
 const double second_ref_decay = mb_sr_err_diff <= 512.0 ? fclamp ( pow ( 1.0 - ( mb_sr_err_diff / 512.0 ) , 0.5 ) , 0.85 , 1.0 ) : 0.85 ;
 return MIN ( second_ref_decay , next_frame -> pcnt_inter ) ;
 }