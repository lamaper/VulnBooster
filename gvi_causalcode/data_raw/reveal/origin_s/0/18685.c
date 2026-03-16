static inline void set_glyph ( hb_glyph_info_t & info , hb_font_t * font ) {
 font -> get_glyph ( info . codepoint , 0 , & info . glyph_index ( ) ) ;
 }