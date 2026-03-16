static inline void output_char ( hb_buffer_t * buffer , hb_codepoint_t unichar , hb_codepoint_t glyph ) {
 buffer -> cur ( ) . glyph_index ( ) = glyph ;
 buffer -> output_glyph ( unichar ) ;
 _hb_glyph_info_set_unicode_props ( & buffer -> prev ( ) , buffer -> unicode ) ;
 }