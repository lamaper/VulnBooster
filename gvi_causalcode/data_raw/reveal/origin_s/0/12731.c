static void update_sharpness ( loop_filter_info_n * lfi , int sharpness_lvl ) {
 int lvl ;
 for ( lvl = 0 ;
 lvl <= MAX_LOOP_FILTER ;
 lvl ++ ) {
 int block_inside_limit = lvl >> ( ( sharpness_lvl > 0 ) + ( sharpness_lvl > 4 ) ) ;
 if ( sharpness_lvl > 0 ) {
 if ( block_inside_limit > ( 9 - sharpness_lvl ) ) block_inside_limit = ( 9 - sharpness_lvl ) ;
 }
 if ( block_inside_limit < 1 ) block_inside_limit = 1 ;
 vpx_memset ( lfi -> lfthr [ lvl ] . lim , block_inside_limit , SIMD_WIDTH ) ;
 vpx_memset ( lfi -> lfthr [ lvl ] . mblim , ( 2 * ( lvl + 2 ) + block_inside_limit ) , SIMD_WIDTH ) ;
 }
 }