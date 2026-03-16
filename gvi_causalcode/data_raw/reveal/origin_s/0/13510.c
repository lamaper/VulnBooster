static hb_face_for_data_closure_t * _hb_face_for_data_closure_create ( hb_blob_t * blob , unsigned int index ) {
 hb_face_for_data_closure_t * closure ;
 closure = ( hb_face_for_data_closure_t * ) malloc ( sizeof ( hb_face_for_data_closure_t ) ) ;
 if ( unlikely ( ! closure ) ) return NULL ;
 closure -> blob = blob ;
 closure -> index = index ;
 return closure ;
 }