static void vga_draw_line8d2 ( VGACommonState * s1 , uint8_t * d , const uint8_t * s , int width ) {
 uint32_t * palette ;
 int x ;
 palette = s1 -> last_palette ;
 width >>= 3 ;
 for ( x = 0 ;
 x < width ;
 x ++ ) {
 PUT_PIXEL2 ( d , 0 , palette [ s [ 0 ] ] ) ;
 PUT_PIXEL2 ( d , 1 , palette [ s [ 1 ] ] ) ;
 PUT_PIXEL2 ( d , 2 , palette [ s [ 2 ] ] ) ;
 PUT_PIXEL2 ( d , 3 , palette [ s [ 3 ] ] ) ;
 d += 32 ;
 s += 4 ;
 }
 }