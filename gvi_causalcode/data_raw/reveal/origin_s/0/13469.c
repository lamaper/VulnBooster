hb_bool_t hb_face_set_user_data ( hb_face_t * face , hb_user_data_key_t * key , void * data , hb_destroy_func_t destroy , hb_bool_t replace ) {
 return hb_object_set_user_data ( face , key , data , destroy , replace ) ;
 }