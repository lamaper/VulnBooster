static inline void decompose_current_character ( const hb_ot_shape_normalize_context_t * c , bool shortest ) {
 hb_buffer_t * const buffer = c -> buffer ;
 hb_codepoint_t glyph ;
 if ( shortest && c -> font -> get_glyph ( buffer -> cur ( ) . codepoint , 0 , & glyph ) ) next_char ( buffer , glyph ) ;
 else if ( decompose ( c , shortest , buffer -> cur ( ) . codepoint ) ) skip_char ( buffer ) ;
 else if ( ! shortest && c -> font -> get_glyph ( buffer -> cur ( ) . codepoint , 0 , & glyph ) ) next_char ( buffer , glyph ) ;
 else if ( decompose_compatibility ( c , buffer -> cur ( ) . codepoint ) ) skip_char ( buffer ) ;
 else next_char ( buffer , glyph ) ;
 }