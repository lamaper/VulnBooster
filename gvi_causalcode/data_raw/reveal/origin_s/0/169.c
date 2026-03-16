static int16_t * raster_block_offset_int16 ( BLOCK_SIZE plane_bsize , int raster_block , int16_t * base ) {
 const int stride = 4 * num_4x4_blocks_wide_lookup [ plane_bsize ] ;
 return base + raster_block_offset ( plane_bsize , raster_block , stride ) ;
 }