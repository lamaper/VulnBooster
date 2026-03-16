int vp9_refining_search_8p_c ( const MACROBLOCK * x , MV * ref_mv , int error_per_bit , int search_range , const vp9_variance_fn_ptr_t * fn_ptr , const MV * center_mv , const uint8_t * second_pred ) {
 const MV neighbors [ 8 ] = {
 {
 - 1 , 0 }
 , {
 0 , - 1 }
 , {
 0 , 1 }
 , {
 1 , 0 }
 , {
 - 1 , - 1 }
 , {
 1 , - 1 }
 , {
 - 1 , 1 }
 , {
 1 , 1 }
 }
 ;
 const MACROBLOCKD * const xd = & x -> e_mbd ;
 const struct buf_2d * const what = & x -> plane [ 0 ] . src ;
 const struct buf_2d * const in_what = & xd -> plane [ 0 ] . pre [ 0 ] ;
 const MV fcenter_mv = {
 center_mv -> row >> 3 , center_mv -> col >> 3 }
 ;
 unsigned int best_sad = fn_ptr -> sdaf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , ref_mv ) , in_what -> stride , second_pred ) + mvsad_err_cost ( x , ref_mv , & fcenter_mv , error_per_bit ) ;
 int i , j ;
 for ( i = 0 ;
 i < search_range ;
 ++ i ) {
 int best_site = - 1 ;
 for ( j = 0 ;
 j < 8 ;
 ++ j ) {
 const MV mv = {
 ref_mv -> row + neighbors [ j ] . row , ref_mv -> col + neighbors [ j ] . col }
 ;
 if ( is_mv_in ( x , & mv ) ) {
 unsigned int sad = fn_ptr -> sdaf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , & mv ) , in_what -> stride , second_pred ) ;
 if ( sad < best_sad ) {
 sad += mvsad_err_cost ( x , & mv , & fcenter_mv , error_per_bit ) ;
 if ( sad < best_sad ) {
 best_sad = sad ;
 best_site = j ;
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
 }
 }
 return best_sad ;
 }