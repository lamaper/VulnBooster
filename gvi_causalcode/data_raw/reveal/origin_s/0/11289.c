static void mongolian_variation_selectors ( hb_buffer_t * buffer ) {
 unsigned int count = buffer -> len ;
 hb_glyph_info_t * info = buffer -> info ;
 for ( unsigned int i = 1 ;
 i < count ;
 i ++ ) if ( unlikely ( hb_in_range ( info [ i ] . codepoint , 0x180Bu , 0x180Du ) ) ) info [ i ] . arabic_shaping_action ( ) = info [ i - 1 ] . arabic_shaping_action ( ) ;
 }