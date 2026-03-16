hb_bool_t hb_blob_set_user_data ( hb_blob_t * blob , hb_user_data_key_t * key , void * data , hb_destroy_func_t destroy , hb_bool_t replace ) {
 return hb_object_set_user_data ( blob , key , data , destroy , replace ) ;
 }