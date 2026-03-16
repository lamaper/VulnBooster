int vp9_rc_bits_per_mb ( FRAME_TYPE frame_type , int qindex , double correction_factor , vpx_bit_depth_t bit_depth ) {
 const double q = vp9_convert_qindex_to_q ( qindex , bit_depth ) ;
 int enumerator = frame_type == KEY_FRAME ? 2700000 : 1800000 ;
 enumerator += ( int ) ( enumerator * q ) >> 12 ;
 return ( int ) ( enumerator * correction_factor / q ) ;
 }