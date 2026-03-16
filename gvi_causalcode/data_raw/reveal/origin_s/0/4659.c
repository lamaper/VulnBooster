static hb_bool_t hb_font_get_glyph_nil ( hb_font_t * font , void * font_data HB_UNUSED , hb_codepoint_t unicode , hb_codepoint_t variation_selector , hb_codepoint_t * glyph , void * user_data HB_UNUSED ) {
 if ( font -> parent ) return font -> parent -> get_glyph ( unicode , variation_selector , glyph ) ;
 * glyph = 0 ;
 return false ;
 }