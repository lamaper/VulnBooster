static hb_bool_t hb_font_get_glyph_h_origin_nil ( hb_font_t * font , void * font_data HB_UNUSED , hb_codepoint_t glyph , hb_position_t * x , hb_position_t * y , void * user_data HB_UNUSED ) {
 if ( font -> parent ) {
 hb_bool_t ret = font -> parent -> get_glyph_h_origin ( glyph , x , y ) ;
 if ( ret ) font -> parent_scale_position ( x , y ) ;
 return ret ;
 }
 * x = * y = 0 ;
 return false ;
 }