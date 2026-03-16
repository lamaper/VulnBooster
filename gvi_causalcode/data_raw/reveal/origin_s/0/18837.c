static int64_t calculate_total_gf_group_bits ( VP9_COMP * cpi , double gf_group_err ) {
 const RATE_CONTROL * const rc = & cpi -> rc ;
 const TWO_PASS * const twopass = & cpi -> twopass ;
 const int max_bits = frame_max_bits ( rc , & cpi -> oxcf ) ;
 int64_t total_group_bits ;
 if ( ( twopass -> kf_group_bits > 0 ) && ( twopass -> kf_group_error_left > 0 ) ) {
 total_group_bits = ( int64_t ) ( twopass -> kf_group_bits * ( gf_group_err / twopass -> kf_group_error_left ) ) ;
 }
 else {
 total_group_bits = 0 ;
 }
 total_group_bits = ( total_group_bits < 0 ) ? : ( total_group_bits > twopass -> kf_group_bits ) ? twopass -> kf_group_bits : total_group_bits ;
 if ( total_group_bits > ( int64_t ) max_bits * rc -> baseline_gf_interval ) total_group_bits = ( int64_t ) max_bits * rc -> baseline_gf_interval ;
 return total_group_bits ;
 }