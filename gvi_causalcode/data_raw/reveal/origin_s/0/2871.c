void hb_face_set_upem ( hb_face_t * face , unsigned int upem ) {
 if ( face -> immutable ) return ;
 face -> upem = upem ;
 }