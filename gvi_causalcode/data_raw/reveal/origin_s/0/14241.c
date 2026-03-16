static uint8_t * block_start ( uint8_t * framebuf , int stride , int mi_row , int mi_col ) {
 return framebuf + ( stride * mi_row * 8 ) + ( mi_col * 8 ) ;
 }