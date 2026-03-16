gr_font * hb_graphite2_font_get_gr_font ( hb_font_t * font ) {
 if ( unlikely ( ! hb_graphite2_shaper_font_data_ensure ( font ) ) ) return NULL ;
 return HB_SHAPER_DATA_GET ( font ) ;
 }