static void vga_draw_line8 ( VGACommonState * s1 , uint8_t * d , const uint8_t * s , int width ) {
 uint32_t * palette ;
 int x ;
 palette = s1 -> last_palette ;
 width >>= 3 ;
 for ( x = 0 ;
 x < width ;
 x ++ ) {
 ( ( uint32_t * ) d ) [ 0 ] = palette [ s [ 0 ] ] ;
 ( ( uint32_t * ) d ) [ 1 ] = palette [ s [ 1 ] ] ;
 ( ( uint32_t * ) d ) [ 2 ] = palette [ s [ 2 ] ] ;
 ( ( uint32_t * ) d ) [ 3 ] = palette [ s [ 3 ] ] ;
 ( ( uint32_t * ) d ) [ 4 ] = palette [ s [ 4 ] ] ;
 ( ( uint32_t * ) d ) [ 5 ] = palette [ s [ 5 ] ] ;
 ( ( uint32_t * ) d ) [ 6 ] = palette [ s [ 6 ] ] ;
 ( ( uint32_t * ) d ) [ 7 ] = palette [ s [ 7 ] ] ;
 d += 32 ;
 s += 8 ;
 }
 }