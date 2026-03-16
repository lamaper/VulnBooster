static int estimate_bits_at_q ( FRAME_TYPE frame_type , int q , int mbs , double correction_factor ) {
 const int bpm = ( int ) ( vp9_rc_bits_per_mb ( frame_type , q , correction_factor ) ) ;
 return ( ( uint64_t ) bpm * mbs ) >> BPER_MB_NORMBITS ;
 }