static void copy_block ( uint8_t * dest , int dest_stride , const uint8_t * src , int src_stride , BLOCK_SIZE bs ) {
 int r ;
 for ( r = 0 ;
 r < heights [ bs ] ;
 ++ r ) {
 vpx_memcpy ( dest , src , widths [ bs ] ) ;
 dest += dest_stride ;
 src += src_stride ;
 }
 }