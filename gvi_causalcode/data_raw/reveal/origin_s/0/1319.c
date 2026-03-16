static int get_active_cq_level ( const RATE_CONTROL * rc , const VP9EncoderConfig * const oxcf ) {
 static const double cq_adjust_threshold = 0.5 ;
 int active_cq_level = oxcf -> cq_level ;
 if ( oxcf -> rc_mode == VPX_CQ && rc -> total_target_bits > 0 ) {
 const double x = ( double ) rc -> total_actual_bits / rc -> total_target_bits ;
 if ( x < cq_adjust_threshold ) {
 active_cq_level = ( int ) ( active_cq_level * x / cq_adjust_threshold ) ;
 }
 }
 return active_cq_level ;
 }