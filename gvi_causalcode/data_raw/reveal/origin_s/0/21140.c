static void vga_draw_line8 ( VGACommonState * vga , uint8_t * d , uint32_t addr , int width ) {
 uint32_t * palette ;
 int x ;
 palette = vga -> last_palette ;
 width >>= 3 ;
 for ( x = 0 ;
 x < width ;
 x ++ ) {
 ( ( uint32_t * ) d ) [ 0 ] = palette [ vga_read_byte ( vga , addr + 0 ) ] ;
 ( ( uint32_t * ) d ) [ 1 ] = palette [ vga_read_byte ( vga , addr + 1 ) ] ;
 ( ( uint32_t * ) d ) [ 2 ] = palette [ vga_read_byte ( vga , addr + 2 ) ] ;
 ( ( uint32_t * ) d ) [ 3 ] = palette [ vga_read_byte ( vga , addr + 3 ) ] ;
 ( ( uint32_t * ) d ) [ 4 ] = palette [ vga_read_byte ( vga , addr + 4 ) ] ;
 ( ( uint32_t * ) d ) [ 5 ] = palette [ vga_read_byte ( vga , addr + 5 ) ] ;
 ( ( uint32_t * ) d ) [ 6 ] = palette [ vga_read_byte ( vga , addr + 6 ) ] ;
 ( ( uint32_t * ) d ) [ 7 ] = palette [ vga_read_byte ( vga , addr + 7 ) ] ;
 d += 32 ;
 addr += 8 ;
 }
 }