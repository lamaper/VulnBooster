static int estimate_bits_at_q ( FRAME_TYPE frame_type , int q , int mbs , double correction_factor , vpx_bit_depth_t bit_depth ) {
 const int bpm = ( int ) ( vp9_rc_bits_per_mb ( frame_type , q , correction_factor , bit_depth ) ) ;
 return ( ( uint64_t ) bpm * mbs ) >> BPER_MB_NORMBITS ;
 }