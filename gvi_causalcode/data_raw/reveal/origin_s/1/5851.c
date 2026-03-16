static hb_glyph_position_t * glyph_position_reference ( hb_glyph_position_t * g ) {
 hb_glyph_position_t * c = ( hb_glyph_position_t * ) calloc ( 1 , sizeof ( hb_glyph_position_t ) ) ;
 if ( unlikely ( ! c ) ) return NULL ;
 * c = * g ;
 return c ;
 }