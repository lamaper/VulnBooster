static void vga_draw_line2 ( VGACommonState * s1 , uint8_t * d , const uint8_t * s , int width ) {
 uint32_t plane_mask , * palette , data , v ;
 int x ;
 palette = s1 -> last_palette ;
 plane_mask = mask16 [ s1 -> ar [ VGA_ATC_PLANE_ENABLE ] & 0xf ] ;
 width >>= 3 ;
 for ( x = 0 ;
 x < width ;
 x ++ ) {
 data = ( ( uint32_t * ) s ) [ 0 ] ;
 data &= plane_mask ;
 v = expand2 [ GET_PLANE ( data , 0 ) ] ;
 v |= expand2 [ GET_PLANE ( data , 2 ) ] << 2 ;
 ( ( uint32_t * ) d ) [ 0 ] = palette [ v >> 12 ] ;
 ( ( uint32_t * ) d ) [ 1 ] = palette [ ( v >> 8 ) & 0xf ] ;
 ( ( uint32_t * ) d ) [ 2 ] = palette [ ( v >> 4 ) & 0xf ] ;
 ( ( uint32_t * ) d ) [ 3 ] = palette [ ( v >> 0 ) & 0xf ] ;
 v = expand2 [ GET_PLANE ( data , 1 ) ] ;
 v |= expand2 [ GET_PLANE ( data , 3 ) ] << 2 ;
 ( ( uint32_t * ) d ) [ 4 ] = palette [ v >> 12 ] ;
 ( ( uint32_t * ) d ) [ 5 ] = palette [ ( v >> 8 ) & 0xf ] ;
 ( ( uint32_t * ) d ) [ 6 ] = palette [ ( v >> 4 ) & 0xf ] ;
 ( ( uint32_t * ) d ) [ 7 ] = palette [ ( v >> 0 ) & 0xf ] ;
 d += 32 ;
 s += 4 ;
 }
 }