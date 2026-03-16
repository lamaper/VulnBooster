void hb_face_set_index ( hb_face_t * face , unsigned int index ) {
 if ( face -> immutable ) return ;
 face -> index = index ;
 }