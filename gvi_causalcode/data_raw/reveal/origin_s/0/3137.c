int vp9_full_range_search_c ( const MACROBLOCK * x , const search_site_config * cfg , MV * ref_mv , MV * best_mv , int search_param , int sad_per_bit , int * num00 , const vp9_variance_fn_ptr_t * fn_ptr , const MV * center_mv ) {
 const MACROBLOCKD * const xd = & x -> e_mbd ;
 const struct buf_2d * const what = & x -> plane [ 0 ] . src ;
 const struct buf_2d * const in_what = & xd -> plane [ 0 ] . pre [ 0 ] ;
 const int range = 64 ;
 const MV fcenter_mv = {
 center_mv -> row >> 3 , center_mv -> col >> 3 }
 ;
 unsigned int best_sad = INT_MAX ;
 int r , c , i ;
 int start_col , end_col , start_row , end_row ;
 ( void ) cfg ;
 ( void ) search_param ;
 clamp_mv ( ref_mv , x -> mv_col_min , x -> mv_col_max , x -> mv_row_min , x -> mv_row_max ) ;
 * best_mv = * ref_mv ;
 * num00 = 11 ;
 best_sad = fn_ptr -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , ref_mv ) , in_what -> stride ) + mvsad_err_cost ( x , ref_mv , & fcenter_mv , sad_per_bit ) ;
 start_row = MAX ( - range , x -> mv_row_min - ref_mv -> row ) ;
 start_col = MAX ( - range , x -> mv_col_min - ref_mv -> col ) ;
 end_row = MIN ( range , x -> mv_row_max - ref_mv -> row ) ;
 end_col = MIN ( range , x -> mv_col_max - ref_mv -> col ) ;
 for ( r = start_row ;
 r <= end_row ;
 ++ r ) {
 for ( c = start_col ;
 c <= end_col ;
 c += 4 ) {
 if ( c + 3 <= end_col ) {
 unsigned int sads [ 4 ] ;
 const uint8_t * addrs [ 4 ] ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 const MV mv = {
 ref_mv -> row + r , ref_mv -> col + c + i }
 ;
 addrs [ i ] = get_buf_from_mv ( in_what , & mv ) ;
 }
 fn_ptr -> sdx4df ( what -> buf , what -> stride , addrs , in_what -> stride , sads ) ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 if ( sads [ i ] < best_sad ) {
 const MV mv = {
 ref_mv -> row + r , ref_mv -> col + c + i }
 ;
 const unsigned int sad = sads [ i ] + mvsad_err_cost ( x , & mv , & fcenter_mv , sad_per_bit ) ;
 if ( sad < best_sad ) {
 best_sad = sad ;
 * best_mv = mv ;
 }
 }
 }
 }
 else {
 for ( i = 0 ;
 i < end_col - c ;
 ++ i ) {
 const MV mv = {
 ref_mv -> row + r , ref_mv -> col + c + i }
 ;
 unsigned int sad = fn_ptr -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & mv ) , in_what -> stride ) ;
 if ( sad < best_sad ) {
 sad += mvsad_err_cost ( x , & mv , & fcenter_mv , sad_per_bit ) ;
 if ( sad < best_sad ) {
 best_sad = sad ;
 * best_mv = mv ;
 }
 }
 }
 }
 }
 }
 return best_sad ;
 }