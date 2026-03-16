static void _hb_face_for_data_closure_destroy ( hb_face_for_data_closure_t * closure ) {
 hb_blob_destroy ( closure -> blob ) ;
 free ( closure ) ;
 }