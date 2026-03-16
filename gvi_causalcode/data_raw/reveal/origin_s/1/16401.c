int vp9_compute_qdelta_by_rate ( const RATE_CONTROL * rc , FRAME_TYPE frame_type , int qindex , double rate_target_ratio ) {
 int target_index = rc -> worst_quality ;
 int i ;
 const int base_bits_per_mb = vp9_rc_bits_per_mb ( frame_type , qindex , 1.0 ) ;
 const int target_bits_per_mb = ( int ) ( rate_target_ratio * base_bits_per_mb ) ;
 for ( i = rc -> best_quality ;
 i < rc -> worst_quality ;
 ++ i ) {
 target_index = i ;
 if ( vp9_rc_bits_per_mb ( frame_type , i , 1.0 ) <= target_bits_per_mb ) break ;
 }
 return target_index - qindex ;
 }