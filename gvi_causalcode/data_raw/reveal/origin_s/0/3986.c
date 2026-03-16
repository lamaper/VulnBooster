static hb_bool_t hb_font_get_glyph_contour_point_nil ( hb_font_t * font , void * font_data HB_UNUSED , hb_codepoint_t glyph , unsigned int point_index , hb_position_t * x , hb_position_t * y , void * user_data HB_UNUSED ) {
 if ( font -> parent ) {
 hb_bool_t ret = font -> parent -> get_glyph_contour_point ( glyph , point_index , x , y ) ;
 if ( ret ) font -> parent_scale_position ( x , y ) ;
 return ret ;
 }
 * x = * y = 0 ;
 return false ;
 }