static YuvPixel mp_get_yuv_from_rgb ( MotionPixelsContext * mp , int x , int y ) {
 int color ;
 color = * ( uint16_t * ) & mp -> frame . data [ 0 ] [ y * mp -> frame . linesize [ 0 ] + x * 2 ] ;
 return mp_rgb_yuv_table [ color ] ;
 }