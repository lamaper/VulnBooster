static void vga_draw_line24_le ( VGACommonState * vga , uint8_t * d , uint32_t addr , int width ) {
 int w ;
 uint32_t r , g , b ;
 w = width ;
 do {
 b = vga_read_byte ( vga , addr + 0 ) ;
 g = vga_read_byte ( vga , addr + 1 ) ;
 r = vga_read_byte ( vga , addr + 2 ) ;
 ( ( uint32_t * ) d ) [ 0 ] = rgb_to_pixel32 ( r , g , b ) ;
 addr += 3 ;
 d += 4 ;
 }
 while ( -- w != 0 ) ;
 }