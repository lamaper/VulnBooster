static hb_position_t hb_font_get_glyph_v_kerning_nil ( hb_font_t * font , void * font_data HB_UNUSED , hb_codepoint_t top_glyph , hb_codepoint_t bottom_glyph , void * user_data HB_UNUSED ) {
 if ( font -> parent ) return font -> parent_scale_y_distance ( font -> parent -> get_glyph_v_kerning ( top_glyph , bottom_glyph ) ) ;
 return 0 ;
 }