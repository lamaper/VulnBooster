static int raster_block_offset ( BLOCK_SIZE plane_bsize , int raster_block , int stride ) {
 const int bw = b_width_log2 ( plane_bsize ) ;
 const int y = 4 * ( raster_block >> bw ) ;
 const int x = 4 * ( raster_block & ( ( 1 << bw ) - 1 ) ) ;
 return y * stride + x ;
 }