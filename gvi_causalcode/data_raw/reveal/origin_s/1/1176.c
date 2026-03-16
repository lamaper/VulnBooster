static void set_partial_b64x64_partition ( MODE_INFO * mi , int mis , int bh_in , int bw_in , int row8x8_remaining , int col8x8_remaining , BLOCK_SIZE bsize , MODE_INFO * * mi_8x8 ) {
 int bh = bh_in ;
 int r , c ;
 for ( r = 0 ;
 r < MI_BLOCK_SIZE ;
 r += bh ) {
 int bw = bw_in ;
 for ( c = 0 ;
 c < MI_BLOCK_SIZE ;
 c += bw ) {
 const int index = r * mis + c ;
 mi_8x8 [ index ] = mi + index ;
 mi_8x8 [ index ] -> mbmi . sb_type = find_partition_size ( bsize , row8x8_remaining - r , col8x8_remaining - c , & bh , & bw ) ;
 }
 }
 }