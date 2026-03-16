static float hb_graphite2_get_advance ( const void * hb_font , unsigned short gid ) {
 return ( ( hb_font_t * ) hb_font ) -> get_glyph_h_advance ( gid ) ;
 }