static inline void handle_variation_selector_cluster ( const hb_ot_shape_normalize_context_t * c , unsigned int end , bool short_circuit ) {
 hb_buffer_t * const buffer = c -> buffer ;
 hb_font_t * const font = c -> font ;
 for ( ;
 buffer -> idx < end - 1 ;
 ) {
 if ( unlikely ( buffer -> unicode -> is_variation_selector ( buffer -> cur ( + 1 ) . codepoint ) ) ) {
 if ( font -> get_glyph ( buffer -> cur ( ) . codepoint , buffer -> cur ( + 1 ) . codepoint , & buffer -> cur ( ) . glyph_index ( ) ) ) {
 buffer -> replace_glyphs ( 2 , 1 , & buffer -> cur ( ) . codepoint ) ;
 }
 else {
 set_glyph ( buffer -> cur ( ) , font ) ;
 buffer -> next_glyph ( ) ;
 set_glyph ( buffer -> cur ( ) , font ) ;
 buffer -> next_glyph ( ) ;
 }
 while ( buffer -> idx < end && unlikely ( buffer -> unicode -> is_variation_selector ( buffer -> cur ( ) . codepoint ) ) ) {
 set_glyph ( buffer -> cur ( ) , font ) ;
 buffer -> next_glyph ( ) ;
 }
 }
 else {
 set_glyph ( buffer -> cur ( ) , font ) ;
 buffer -> next_glyph ( ) ;
 }
 }
 if ( likely ( buffer -> idx < end ) ) {
 set_glyph ( buffer -> cur ( ) , font ) ;
 buffer -> next_glyph ( ) ;
 }
 }