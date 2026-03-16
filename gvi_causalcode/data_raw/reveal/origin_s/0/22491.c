static void vga_draw_glyph9 ( uint8_t * d , int linesize , const uint8_t * font_ptr , int h , uint32_t fgcol , uint32_t bgcol , int dup9 ) {
 uint32_t font_data , xorcol , v ;
 xorcol = bgcol ^ fgcol ;
 do {
 font_data = font_ptr [ 0 ] ;
 ( ( uint32_t * ) d ) [ 0 ] = ( - ( ( font_data >> 7 ) ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 1 ] = ( - ( ( font_data >> 6 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 2 ] = ( - ( ( font_data >> 5 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 3 ] = ( - ( ( font_data >> 4 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 4 ] = ( - ( ( font_data >> 3 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 5 ] = ( - ( ( font_data >> 2 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 6 ] = ( - ( ( font_data >> 1 ) & 1 ) & xorcol ) ^ bgcol ;
 v = ( - ( ( font_data >> 0 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 7 ] = v ;
 if ( dup9 ) ( ( uint32_t * ) d ) [ 8 ] = v ;
 else ( ( uint32_t * ) d ) [ 8 ] = bgcol ;
 font_ptr += 4 ;
 d += linesize ;
 }
 while ( -- h ) ;
 }