static void * i_alloc_struct ( gs_memory_t * mem , gs_memory_type_ptr_t pstype , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 uint size = pstype -> ssize ;
 obj_header_t * obj ;
 obj_header_t * * pfl ;


 IF_FREELIST_ALLOC ( obj , imem , size , pstype , pfl ) alloc_trace ( ":+<f" , imem , cname , pstype , size , obj ) ;
 ELSEIF_BIG_FREELIST_ALLOC ( obj , imem , size , pstype ) alloc_trace ( ":+<F" , imem , cname , pstype , size , obj ) ;
 ELSEIF_LIFO_ALLOC ( obj , imem , size , pstype ) alloc_trace ( ":+< " , imem , cname , pstype , size , obj ) ;
 ELSE_ALLOC {
 obj = alloc_obj ( imem , size , pstype , 0 , cname ) ;
 if ( obj == 0 ) return 0 ;
 alloc_trace ( ":+<." , imem , cname , pstype , size , obj ) ;
 }


 }