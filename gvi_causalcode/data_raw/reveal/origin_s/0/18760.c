void hb_face_set_glyph_count ( hb_face_t * face , unsigned int glyph_count ) {
 if ( face -> immutable ) return ;
 face -> num_glyphs = glyph_count ;
 }