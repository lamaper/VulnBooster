static void init_minq_luts ( int * kf_low_m , int * kf_high_m , int * arfgf_low , int * arfgf_high , int * inter , int * rtc , vpx_bit_depth_t bit_depth ) {
 int i ;
 for ( i = 0 ;
 i < QINDEX_RANGE ;
 i ++ ) {
 const double maxq = vp9_convert_qindex_to_q ( i , bit_depth ) ;
 kf_low_m [ i ] = get_minq_index ( maxq , 0.000001 , - 0.0004 , 0.150 , bit_depth ) ;
 kf_high_m [ i ] = get_minq_index ( maxq , 0.0000021 , - 0.00125 , 0.55 , bit_depth ) ;
 arfgf_low [ i ] = get_minq_index ( maxq , 0.0000015 , - 0.0009 , 0.30 , bit_depth ) ;
 arfgf_high [ i ] = get_minq_index ( maxq , 0.0000021 , - 0.00125 , 0.55 , bit_depth ) ;
 inter [ i ] = get_minq_index ( maxq , 0.00000271 , - 0.00113 , 0.90 , bit_depth ) ;
 rtc [ i ] = get_minq_index ( maxq , 0.00000271 , - 0.00113 , 0.70 , bit_depth ) ;
 }
 }