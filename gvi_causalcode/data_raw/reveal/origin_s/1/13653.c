static void vga_draw_line16_le ( VGACommonState * s1 , uint8_t * d , const uint8_t * s , int width ) {
 int w ;
 uint32_t v , r , g , b ;
 w = width ;
 do {
 v = lduw_le_p ( ( void * ) s ) ;
 r = ( v >> 8 ) & 0xf8 ;
 g = ( v >> 3 ) & 0xfc ;
 b = ( v << 3 ) & 0xf8 ;
 ( ( uint32_t * ) d ) [ 0 ] = rgb_to_pixel32 ( r , g , b ) ;
 s += 2 ;
 d += 4 ;
 }
 while ( -- w != 0 ) ;
 }