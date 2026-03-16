int vp9_diamond_search_sad_c ( const MACROBLOCK * x , const search_site_config * cfg , MV * ref_mv , MV * best_mv , int search_param , int sad_per_bit , int * num00 , const vp9_variance_fn_ptr_t * fn_ptr , const MV * center_mv ) {
 int i , j , step ;
 const MACROBLOCKD * const xd = & x -> e_mbd ;
 uint8_t * what = x -> plane [ 0 ] . src . buf ;
 const int what_stride = x -> plane [ 0 ] . src . stride ;
 const uint8_t * in_what ;
 const int in_what_stride = xd -> plane [ 0 ] . pre [ 0 ] . stride ;
 const uint8_t * best_address ;
 unsigned int bestsad = INT_MAX ;
 int best_site = 0 ;
 int last_site = 0 ;
 int ref_row ;
 int ref_col ;
 const search_site * ss = & cfg -> ss [ search_param * cfg -> searches_per_step ] ;
 const int tot_steps = ( cfg -> ss_count / cfg -> searches_per_step ) - search_param ;
 const MV fcenter_mv = {
 center_mv -> row >> 3 , center_mv -> col >> 3 }
 ;
 clamp_mv ( ref_mv , x -> mv_col_min , x -> mv_col_max , x -> mv_row_min , x -> mv_row_max ) ;
 ref_row = ref_mv -> row ;
 ref_col = ref_mv -> col ;
 * num00 = 0 ;
 best_mv -> row = ref_row ;
 best_mv -> col = ref_col ;
 in_what = xd -> plane [ 0 ] . pre [ 0 ] . buf + ref_row * in_what_stride + ref_col ;
 best_address = in_what ;
 bestsad = fn_ptr -> sdf ( what , what_stride , in_what , in_what_stride ) + mvsad_err_cost ( x , best_mv , & fcenter_mv , sad_per_bit ) ;
 i = 1 ;
 for ( step = 0 ;
 step < tot_steps ;
 step ++ ) {
 int all_in = 1 , t ;
 all_in &= ( ( best_mv -> row + ss [ i ] . mv . row ) > x -> mv_row_min ) ;
 all_in &= ( ( best_mv -> row + ss [ i + 1 ] . mv . row ) < x -> mv_row_max ) ;
 all_in &= ( ( best_mv -> col + ss [ i + 2 ] . mv . col ) > x -> mv_col_min ) ;
 all_in &= ( ( best_mv -> col + ss [ i + 3 ] . mv . col ) < x -> mv_col_max ) ;
 if ( all_in ) {
 unsigned int sad_array [ 4 ] ;
 for ( j = 0 ;
 j < cfg -> searches_per_step ;
 j += 4 ) {
 unsigned char const * block_offset [ 4 ] ;
 for ( t = 0 ;
 t < 4 ;
 t ++ ) block_offset [ t ] = ss [ i + t ] . offset + best_address ;
 fn_ptr -> sdx4df ( what , what_stride , block_offset , in_what_stride , sad_array ) ;
 for ( t = 0 ;
 t < 4 ;
 t ++ , i ++ ) {
 if ( sad_array [ t ] < bestsad ) {
 const MV this_mv = {
 best_mv -> row + ss [ i ] . mv . row , best_mv -> col + ss [ i ] . mv . col }
 ;
 sad_array [ t ] += mvsad_err_cost ( x , & this_mv , & fcenter_mv , sad_per_bit ) ;
 if ( sad_array [ t ] < bestsad ) {
 bestsad = sad_array [ t ] ;
 best_site = i ;
 }
 }
 }
 }
 }
 else {
 for ( j = 0 ;
 j < cfg -> searches_per_step ;
 j ++ ) {
 const MV this_mv = {
 best_mv -> row + ss [ i ] . mv . row , best_mv -> col + ss [ i ] . mv . col }
 ;
 if ( is_mv_in ( x , & this_mv ) ) {
 const uint8_t * const check_here = ss [ i ] . offset + best_address ;
 unsigned int thissad = fn_ptr -> sdf ( what , what_stride , check_here , in_what_stride ) ;
 if ( thissad < bestsad ) {
 thissad += mvsad_err_cost ( x , & this_mv , & fcenter_mv , sad_per_bit ) ;
 if ( thissad < bestsad ) {
 bestsad = thissad ;
 best_site = i ;
 }
 }
 }
 i ++ ;
 }
 }
 if ( best_site != last_site ) {
 best_mv -> row += ss [ best_site ] . mv . row ;
 best_mv -> col += ss [ best_site ] . mv . col ;
 best_address += ss [ best_site ] . offset ;
 last_site = best_site ;

 const MV this_mv = {
 best_mv -> row + ss [ best_site ] . mv . row , best_mv -> col + ss [ best_site ] . mv . col }
 ;
 if ( is_mv_in ( x , & this_mv ) ) {
 const uint8_t * const check_here = ss [ best_site ] . offset + best_address ;
 unsigned int thissad = fn_ptr -> sdf ( what , what_stride , check_here , in_what_stride ) ;
 if ( thissad < bestsad ) {
 thissad += mvsad_err_cost ( x , & this_mv , & fcenter_mv , sad_per_bit ) ;
 if ( thissad < bestsad ) {
 bestsad = thissad ;
 best_mv -> row += ss [ best_site ] . mv . row ;
 best_mv -> col += ss [ best_site ] . mv . col ;
 best_address += ss [ best_site ] . offset ;
 continue ;
 }
 }
 }
 break ;
 }
 ;

 else if ( best_address == in_what ) {
 ( * num00 ) ++ ;
 }
 }
 return bestsad ;
 }