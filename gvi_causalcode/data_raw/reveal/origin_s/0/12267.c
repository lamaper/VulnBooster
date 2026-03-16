static void cdxl_decode_rgb ( CDXLVideoContext * c , AVFrame * frame ) {
 uint32_t * new_palette = ( uint32_t * ) frame -> data [ 1 ] ;
 import_palette ( c , new_palette ) ;
 import_format ( c , frame -> linesize [ 0 ] , frame -> data [ 0 ] ) ;
 }