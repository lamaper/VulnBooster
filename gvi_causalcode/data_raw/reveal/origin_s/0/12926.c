static void i_set_object_type ( gs_memory_t * mem , void * ptr , gs_memory_type_ptr_t type ) {
 obj_header_t * pp ;
 if ( ptr == 0 ) return ;
 pp = ( obj_header_t * ) ptr - 1 ;
 pp -> o_type = type ;
 }