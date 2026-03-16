hb_face_t * hb_face_create ( hb_blob_t * blob , unsigned int index ) {
 hb_face_t * face ;
 if ( unlikely ( ! blob ) ) blob = hb_blob_get_empty ( ) ;
 hb_face_for_data_closure_t * closure = _hb_face_for_data_closure_create ( OT : : Sanitizer < OT : : OpenTypeFontFile > : : sanitize ( hb_blob_reference ( blob ) ) , index ) ;
 if ( unlikely ( ! closure ) ) return hb_face_get_empty ( ) ;
 face = hb_face_create_for_tables ( _hb_face_for_data_reference_table , closure , ( hb_destroy_func_t ) _hb_face_for_data_closure_destroy ) ;
 hb_face_set_index ( face , index ) ;
 return face ;
 }