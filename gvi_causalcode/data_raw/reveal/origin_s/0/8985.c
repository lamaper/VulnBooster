static void * i_alloc_struct_immovable ( gs_memory_t * mem , gs_memory_type_ptr_t pstype , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 uint size = pstype -> ssize ;
 obj_header_t * obj ;


 obj = alloc_obj ( imem , size , pstype , ALLOC_IMMOVABLE | ALLOC_DIRECT , cname ) ;
 alloc_trace ( "|+<." , imem , cname , pstype , size , obj ) ;
 return obj ;
 }