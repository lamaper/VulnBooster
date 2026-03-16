static inline void next_char ( hb_buffer_t * buffer , hb_codepoint_t glyph ) {
 buffer -> cur ( ) . glyph_index ( ) = glyph ;
 buffer -> next_glyph ( ) ;
 }