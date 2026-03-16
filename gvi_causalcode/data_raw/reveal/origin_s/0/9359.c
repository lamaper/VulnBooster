static void vga_draw_line8d2 ( VGACommonState * vga , uint8_t * d , uint32_t addr , int width ) {
 uint32_t * palette ;
 int x ;
 palette = vga -> last_palette ;
 width >>= 3 ;
 for ( x = 0 ;
 x < width ;
 x ++ ) {
 PUT_PIXEL2 ( d , 0 , palette [ vga_read_byte ( vga , addr + 0 ) ] ) ;
 PUT_PIXEL2 ( d , 1 , palette [ vga_read_byte ( vga , addr + 1 ) ] ) ;
 PUT_PIXEL2 ( d , 2 , palette [ vga_read_byte ( vga , addr + 2 ) ] ) ;
 PUT_PIXEL2 ( d , 3 , palette [ vga_read_byte ( vga , addr + 3 ) ] ) ;
 d += 32 ;
 addr += 4 ;
 }
 }