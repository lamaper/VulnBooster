gr_face * hb_graphite2_face_get_gr_face ( hb_face_t * face ) {
 if ( unlikely ( ! hb_graphite2_shaper_face_data_ensure ( face ) ) ) return NULL ;
 return HB_SHAPER_DATA_GET ( face ) -> grface ;
 }