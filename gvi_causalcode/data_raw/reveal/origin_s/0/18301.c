static void vga_draw_glyph16 ( uint8_t * d , int linesize , const uint8_t * font_ptr , int h , uint32_t fgcol , uint32_t bgcol ) {
 uint32_t font_data , xorcol ;
 xorcol = bgcol ^ fgcol ;
 do {
 font_data = font_ptr [ 0 ] ;
 vga_draw_glyph_line ( d , expand4to8 [ font_data >> 4 ] , xorcol , bgcol ) ;
 vga_draw_glyph_line ( d + 32 , expand4to8 [ font_data & 0x0f ] , xorcol , bgcol ) ;
 font_ptr += 4 ;
 d += linesize ;
 }
 while ( -- h ) ;
 }