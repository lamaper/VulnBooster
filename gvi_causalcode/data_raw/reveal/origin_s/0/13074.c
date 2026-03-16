static byte * i_alloc_byte_array_immovable ( gs_memory_t * mem , uint num_elements , uint elt_size , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 obj_header_t * obj ;
 ulong lsize ;


 obj = alloc_obj ( imem , lsize , & st_bytes , ALLOC_IMMOVABLE | ALLOC_DIRECT , cname ) ;
 if_debug6m ( 'A' , mem , "[a%d|+b.]%s -bytes-*(%lu=%u*%u) = 0x%lx\n" , alloc_trace_space ( imem ) , client_name_string ( cname ) , ( ulong ) num_elements * elt_size , num_elements , elt_size , ( ulong ) obj ) ;
 return ( byte * ) obj ;
 }