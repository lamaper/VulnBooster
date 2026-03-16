static hb_bool_t hb_font_get_glyph_extents_nil ( hb_font_t * font , void * font_data HB_UNUSED , hb_codepoint_t glyph , hb_glyph_extents_t * extents , void * user_data HB_UNUSED ) {
 if ( font -> parent ) {
 hb_bool_t ret = font -> parent -> get_glyph_extents ( glyph , extents ) ;
 if ( ret ) {
 font -> parent_scale_position ( & extents -> x_bearing , & extents -> y_bearing ) ;
 font -> parent_scale_distance ( & extents -> width , & extents -> height ) ;
 }
 return ret ;
 }
 memset ( extents , 0 , sizeof ( * extents ) ) ;
 return false ;
 }