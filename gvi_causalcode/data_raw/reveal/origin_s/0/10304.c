static BLOCK_SIZE find_partition_size ( BLOCK_SIZE bsize , int rows_left , int cols_left , int * bh , int * bw ) {
 if ( rows_left <= 0 || cols_left <= 0 ) {
 return MIN ( bsize , BLOCK_8X8 ) ;
 }
 else {
 for ( ;
 bsize > 0 ;
 bsize -= 3 ) {
 * bh = num_8x8_blocks_high_lookup [ bsize ] ;
 * bw = num_8x8_blocks_wide_lookup [ bsize ] ;
 if ( ( * bh <= rows_left ) && ( * bw <= cols_left ) ) {
 break ;
 }
 }
 }
 return bsize ;
 }