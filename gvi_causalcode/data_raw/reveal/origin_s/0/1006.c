static void vga_draw_line2d2 ( VGACommonState * vga , uint8_t * d , uint32_t addr , int width ) {
 uint32_t plane_mask , * palette , data , v ;
 int x ;
 palette = vga -> last_palette ;
 plane_mask = mask16 [ vga -> ar [ VGA_ATC_PLANE_ENABLE ] & 0xf ] ;
 width >>= 3 ;
 for ( x = 0 ;
 x < width ;
 x ++ ) {
 data = vga_read_dword_le ( vga , addr ) ;
 data &= plane_mask ;
 v = expand2 [ GET_PLANE ( data , 0 ) ] ;
 v |= expand2 [ GET_PLANE ( data , 2 ) ] << 2 ;
 PUT_PIXEL2 ( d , 0 , palette [ v >> 12 ] ) ;
 PUT_PIXEL2 ( d , 1 , palette [ ( v >> 8 ) & 0xf ] ) ;
 PUT_PIXEL2 ( d , 2 , palette [ ( v >> 4 ) & 0xf ] ) ;
 PUT_PIXEL2 ( d , 3 , palette [ ( v >> 0 ) & 0xf ] ) ;
 v = expand2 [ GET_PLANE ( data , 1 ) ] ;
 v |= expand2 [ GET_PLANE ( data , 3 ) ] << 2 ;
 PUT_PIXEL2 ( d , 4 , palette [ v >> 12 ] ) ;
 PUT_PIXEL2 ( d , 5 , palette [ ( v >> 8 ) & 0xf ] ) ;
 PUT_PIXEL2 ( d , 6 , palette [ ( v >> 4 ) & 0xf ] ) ;
 PUT_PIXEL2 ( d , 7 , palette [ ( v >> 0 ) & 0xf ] ) ;
 d += 64 ;
 addr += 4 ;
 }
 }