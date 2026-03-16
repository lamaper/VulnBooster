static hb_position_t hb_font_get_glyph_h_kerning_nil ( hb_font_t * font , void * font_data HB_UNUSED , hb_codepoint_t left_glyph , hb_codepoint_t right_glyph , void * user_data HB_UNUSED ) {
 if ( font -> parent ) return font -> parent_scale_x_distance ( font -> parent -> get_glyph_h_kerning ( left_glyph , right_glyph ) ) ;
 return 0 ;
 }