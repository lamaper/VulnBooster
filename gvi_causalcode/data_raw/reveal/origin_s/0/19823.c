static hb_bool_t hb_font_get_glyph_from_name_nil ( hb_font_t * font , void * font_data HB_UNUSED , const char * name , int len , hb_codepoint_t * glyph , void * user_data HB_UNUSED ) {
 if ( font -> parent ) return font -> parent -> get_glyph_from_name ( name , len , glyph ) ;
 * glyph = 0 ;
 return false ;
 }