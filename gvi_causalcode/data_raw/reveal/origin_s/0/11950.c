hb_bool_t hb_shape_plan_set_user_data ( hb_shape_plan_t * shape_plan , hb_user_data_key_t * key , void * data , hb_destroy_func_t destroy , hb_bool_t replace ) {
 return hb_object_set_user_data ( shape_plan , key , data , destroy , replace ) ;
 }