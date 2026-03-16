static hb_glyph_info_t * glyph_info_reference ( hb_glyph_info_t * g ) {
 hb_glyph_info_t * c = ( hb_glyph_info_t * ) calloc ( 1 , sizeof ( hb_glyph_info_t ) ) ;
 if ( unlikely ( ! c ) ) return NULL ;
 * c = * g ;
 return c ;
 }