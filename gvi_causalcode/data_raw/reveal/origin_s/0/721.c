static uint i_object_size ( gs_memory_t * mem , const void * obj ) {
 return pre_obj_contents_size ( ( const obj_header_t * ) obj - 1 ) ;
 }