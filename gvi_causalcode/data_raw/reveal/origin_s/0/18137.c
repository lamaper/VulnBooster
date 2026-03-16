hb_face_t * hb_face_create_for_tables ( hb_reference_table_func_t reference_table_func , void * user_data , hb_destroy_func_t destroy ) {
 hb_face_t * face ;
 if ( ! reference_table_func || ! ( face = hb_object_create < hb_face_t > ( ) ) ) {
 if ( destroy ) destroy ( user_data ) ;
 return hb_face_get_empty ( ) ;
 }
 face -> reference_table_func = reference_table_func ;
 face -> user_data = user_data ;
 face -> destroy = destroy ;
 face -> upem = 0 ;
 face -> num_glyphs = ( unsigned int ) - 1 ;
 return face ;
 }