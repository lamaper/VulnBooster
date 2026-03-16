int vp9_full_search_sadx8 ( const MACROBLOCK * x , const MV * ref_mv , int sad_per_bit , int distance , const vp9_variance_fn_ptr_t * fn_ptr , const MV * center_mv , MV * best_mv ) {
 int r ;
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
 unsigned int best_sad = fn_ptr -> sdf ( what -> buf , what -> stride , get_buf_from_mv ( in_what , ref_mv ) , in_what -> stride ) + mvsad_err_cost ( x , ref_mv , & fcenter_mv , sad_per_bit ) ;
 * best_mv = * ref_mv ;
 for ( r = row_min ;
 r < row_max ;
 ++ r ) {
 int c = col_min ;
 const uint8_t * check_here = & in_what -> buf [ r * in_what -> stride + c ] ;
 if ( fn_ptr -> sdx8f != NULL ) {
 while ( ( c + 7 ) < col_max ) {
 int i ;
 unsigned int sads [ 8 ] ;
 fn_ptr -> sdx8f ( what -> buf , what -> stride , check_here , in_what -> stride , sads ) ;
 for ( i = 0 ;
 i < 8 ;
 ++ i ) {
 unsigned int sad = sads [ i ] ;
 if ( sad < best_sad ) {
 const MV mv = {
 r , c }
 ;
 sad += mvsad_err_cost ( x , & mv , & fcenter_mv , sad_per_bit ) ;
 if ( sad < best_sad ) {
 best_sad = sad ;
 * best_mv = mv ;
 }
 }
 ++ check_here ;
 ++ c ;
 }
 }
 }
 if ( fn_ptr -> sdx3f != NULL ) {
 while ( ( c + 2 ) < col_max ) {
 int i ;
 unsigned int sads [ 3 ] ;
 fn_ptr -> sdx3f ( what -> buf , what -> stride , check_here , in_what -> stride , sads ) ;
 for ( i = 0 ;
 i < 3 ;
 ++ i ) {
 unsigned int sad = sads [ i ] ;
 if ( sad < best_sad ) {
 const MV mv = {
 r , c }
 ;
 sad += mvsad_err_cost ( x , & mv , & fcenter_mv , sad_per_bit ) ;
 if ( sad < best_sad ) {
 best_sad = sad ;
 * best_mv = mv ;
 }
 }
 ++ check_here ;
 ++ c ;
 }
 }
 }
 while ( c < col_max ) {
 unsigned int sad = fn_ptr -> sdf ( what -> buf , what -> stride , check_here , in_what -> stride ) ;
 if ( sad < best_sad ) {
 const MV mv = {
 r , c }
 ;
 sad += mvsad_err_cost ( x , & mv , & fcenter_mv , sad_per_bit ) ;
 if ( sad < best_sad ) {
 best_sad = sad ;
 * best_mv = mv ;
 }
 }
 ++ check_here ;
 ++ c ;
 }
 }
 return best_sad ;
 }