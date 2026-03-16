static inline void vga_draw_glyph_line ( uint8_t * d , uint32_t font_data , uint32_t xorcol , uint32_t bgcol ) {
 ( ( uint32_t * ) d ) [ 0 ] = ( - ( ( font_data >> 7 ) ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 1 ] = ( - ( ( font_data >> 6 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 2 ] = ( - ( ( font_data >> 5 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 3 ] = ( - ( ( font_data >> 4 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 4 ] = ( - ( ( font_data >> 3 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 5 ] = ( - ( ( font_data >> 2 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 6 ] = ( - ( ( font_data >> 1 ) & 1 ) & xorcol ) ^ bgcol ;
 ( ( uint32_t * ) d ) [ 7 ] = ( - ( ( font_data >> 0 ) & 1 ) & xorcol ) ^ bgcol ;
 }