static hb_bool_t hb_font_get_glyph_name_nil ( hb_font_t * font , void * font_data HB_UNUSED , hb_codepoint_t glyph , char * name , unsigned int size , void * user_data HB_UNUSED ) {
 if ( font -> parent ) return font -> parent -> get_glyph_name ( glyph , name , size ) ;
 if ( size ) * name = '\0' ;
 return false ;
 }