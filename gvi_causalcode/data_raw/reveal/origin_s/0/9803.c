hb_bool_t hb_font_funcs_set_user_data ( hb_font_funcs_t * ffuncs , hb_user_data_key_t * key , void * data , hb_destroy_func_t destroy , hb_bool_t replace ) {
 return hb_object_set_user_data ( ffuncs , key , data , destroy , replace ) ;
 }