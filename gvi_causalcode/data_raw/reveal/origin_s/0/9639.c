static void mp_set_rgb_from_yuv ( MotionPixelsContext * mp , int x , int y , const YuvPixel * p ) {
 int color ;
 color = mp_yuv_to_rgb ( p -> y , p -> v , p -> u , 1 ) ;
 * ( uint16_t * ) & mp -> frame . data [ 0 ] [ y * mp -> frame . linesize [ 0 ] + x * 2 ] = color ;
 }