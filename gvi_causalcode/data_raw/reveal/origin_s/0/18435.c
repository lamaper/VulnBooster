static gs_memory_type_ptr_t i_object_type ( const gs_memory_t * mem , const void * obj ) {
 return ( ( const obj_header_t * ) obj - 1 ) -> o_type ;
 }