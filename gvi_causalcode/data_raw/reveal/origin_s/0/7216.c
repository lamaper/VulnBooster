int vp9_compute_qdelta ( const RATE_CONTROL * rc , double qstart , double qtarget , vpx_bit_depth_t bit_depth ) {
 int start_index = rc -> worst_quality ;
 int target_index = rc -> worst_quality ;
 int i ;
 for ( i = rc -> best_quality ;
 i < rc -> worst_quality ;
 ++ i ) {
 start_index = i ;
 if ( vp9_convert_qindex_to_q ( i , bit_depth ) >= qstart ) break ;
 }
 for ( i = rc -> best_quality ;
 i < rc -> worst_quality ;
 ++ i ) {
 target_index = i ;
 if ( vp9_convert_qindex_to_q ( i , bit_depth ) >= qtarget ) break ;
 }
 return target_index - start_index ;
 }