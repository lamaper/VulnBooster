int vp9_full_search_sad_c ( const MACROBLOCK * x , const MV * ref_mv , int sad_per_bit , int distance , const vp9_variance_fn_ptr_t * fn_ptr , const MV * center_mv , MV * best_mv ) {
 int r , c ;
 const MACROBLOCKD * const xd = & x -> e_mbd ;
 const struct buf_2d * const what = & x -> plane [ 0 ] . src ;
 const struct buf_2d * const in_what = & xd -> plane [ 0 ] . pre [ 0 ] ;
 const int row_min = MAX ( ref_mv -> row - distance , x -> mv_row_min ) ;
 const int row_max = MIN ( ref_mv -> row + distance , x -> mv_row_max ) ;
 const int col_min = MAX ( ref_mv -> col - distance , x -> mv_col_min ) ;
 const int col_max = MIN ( ref_mv -> col + distance , x -> mv_col_max ) ;
 const MV fcenter_mv = {
 center_mv -> row >> 3 , center_mv -> col >> 3 }
 ;
 int best_sad = fn_ptr -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , ref_mv ) , in_what -> stride ) + mvsad_err_cost ( x , ref_mv , & fcenter_mv , sad_per_bit ) ;
 * best_mv = * ref_mv ;
 for ( r = row_min ;
 r < row_max ;
 ++ r ) {
 for ( c = col_min ;
 c < col_max ;
 ++ c ) {
 const MV mv = {
 r , c }
 ;
 const int sad = fn_ptr -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & mv ) , in_what -> stride ) + mvsad_err_cost ( x , & mv , & fcenter_mv , sad_per_bit ) ;
 if ( sad < best_sad ) {
 best_sad = sad ;
 * best_mv = mv ;
 }
 }
 }
 return best_sad ;
 }