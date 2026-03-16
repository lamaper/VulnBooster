void vp9_rc_init_minq_luts ( ) {
 int i ;
 for ( i = 0 ;
 i < QINDEX_RANGE ;
 i ++ ) {
 const double maxq = vp9_convert_qindex_to_q ( i ) ;
 kf_low_motion_minq [ i ] = get_minq_index ( maxq , 0.000001 , - 0.0004 , 0.125 ) ;
 kf_high_motion_minq [ i ] = get_minq_index ( maxq , 0.000002 , - 0.0012 , 0.50 ) ;
 arfgf_low_motion_minq [ i ] = get_minq_index ( maxq , 0.0000015 , - 0.0009 , 0.30 ) ;
 arfgf_high_motion_minq [ i ] = get_minq_index ( maxq , 0.0000021 , - 0.00125 , 0.50 ) ;
 inter_minq [ i ] = get_minq_index ( maxq , 0.00000271 , - 0.00113 , 0.90 ) ;
 rtc_minq [ i ] = get_minq_index ( maxq , 0.00000271 , - 0.00113 , 0.70 ) ;
 }
 }