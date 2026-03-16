void * hb_font_funcs_get_user_data ( hb_font_funcs_t * ffuncs , hb_user_data_key_t * key ) {
 return hb_object_get_user_data ( ffuncs , key ) ;
 }