int vp9_rc_bits_per_mb ( FRAME_TYPE frame_type , int qindex , double correction_factor ) {
 const double q = vp9_convert_qindex_to_q ( qindex ) ;
 int enumerator = frame_type == KEY_FRAME ? 3300000 : 2250000 ;
 enumerator += ( int ) ( enumerator * q ) >> 12 ;
 return ( int ) ( enumerator * correction_factor / q ) ;
 }