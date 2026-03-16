int vp9_refining_search_sad_c ( const MACROBLOCK * x , MV * ref_mv , int error_per_bit , int search_range , const vp9_variance_fn_ptr_t * fn_ptr , const MV * center_mv ) {
 const MACROBLOCKD * const xd = & x -> e_mbd ;
 const MV neighbors [ 4 ] = {
 {
 - 1 , 0 }
 , {
 0 , - 1 }
 , {
 0 , 1 }
 , {
 1 , 0 }
 }
 ;
 const struct buf_2d * const what = & x -> plane [ 0 ] . src ;
 const struct buf_2d * const in_what = & xd -> plane [ 0 ] . pre [ 0 ] ;
 const MV fcenter_mv = {
 center_mv -> row >> 3 , center_mv -> col >> 3 }
 ;
 const uint8_t * best_address = get_buf_from_mv ( in_what , ref_mv ) ;
 unsigned int best_sad = fn_ptr -> sdf ( what -> buf , what -> stride , best_address , in_what -> stride ) + mvsad_err_cost ( x , ref_mv , & fcenter_mv , error_per_bit ) ;
 int i , j ;
 for ( i = 0 ;
 i < search_range ;
 i ++ ) {
 int best_site = - 1 ;
 const int all_in = ( ( ref_mv -> row - 1 ) > x -> mv_row_min ) & ( ( ref_mv -> row + 1 ) < x -> mv_row_max ) & ( ( ref_mv -> col - 1 ) > x -> mv_col_min ) & ( ( ref_mv -> col + 1 ) < x -> mv_col_max ) ;
 if ( all_in ) {
 unsigned int sads [ 4 ] ;
 const uint8_t * const positions [ 4 ] = {
 best_address - in_what -> stride , best_address - 1 , best_address + 1 , best_address + in_what -> stride }
 ;
 fn_ptr -> sdx4df ( what -> buf , what -> stride , positions , in_what -> stride , sads ) ;
 for ( j = 0 ;
 j < 4 ;
 ++ j ) {
 if ( sads [ j ] < best_sad ) {
 const MV mv = {
 ref_mv -> row + neighbors [ j ] . row , ref_mv -> col + neighbors [ j ] . col }
 ;
 sads [ j ] += mvsad_err_cost ( x , & mv , & fcenter_mv , error_per_bit ) ;
 if ( sads [ j ] < best_sad ) {
 best_sad = sads [ j ] ;
 best_site = j ;
 }
 }
 }
 }
 else {
 for ( j = 0 ;
 j < 4 ;
 ++ j ) {
 const MV mv = {
 ref_mv -> row + neighbors [ j ] . row , ref_mv -> col + neighbors [ j ] . col }
 ;
 if ( is_mv_in ( x , & mv ) ) {
 unsigned int sad = fn_ptr -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & mv ) , in_what -> stride ) ;
 if ( sad < best_sad ) {
 sad += mvsad_err_cost ( x , & mv , & fcenter_mv , error_per_bit ) ;
 if ( sad < best_sad ) {
 best_sad = sad ;
 best_site = j ;
 }
 }
 }
 }
 }
 if ( best_site == - 1 ) {
 break ;
 }
 else {
 ref_mv -> row += neighbors [ best_site ] . row ;
 ref_mv -> col += neighbors [ best_site ] . col ;
 best_address = get_buf_from_mv ( in_what , ref_mv ) ;
 }
 }
 return best_sad ;
 }