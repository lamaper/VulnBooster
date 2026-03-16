static void vga_draw_glyph8 ( uint8_t * d , int linesize , const uint8_t * font_ptr , int h , uint32_t fgcol , uint32_t bgcol ) {
 uint32_t font_data , xorcol ;
 xorcol = bgcol ^ fgcol ;
 do {
 font_data = font_ptr [ 0 ] ;
 vga_draw_glyph_line ( d , font_data , xorcol , bgcol ) ;
 font_ptr += 4 ;
 d += linesize ;
 }
 while ( -- h ) ;
 }