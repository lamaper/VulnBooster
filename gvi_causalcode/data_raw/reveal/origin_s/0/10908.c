static void * i_resize_object ( gs_memory_t * mem , void * obj , uint new_num_elements , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 obj_header_t * pp = ( obj_header_t * ) obj - 1 ;
 gs_memory_type_ptr_t pstype = pp -> o_type ;
 ulong old_size = pre_obj_contents_size ( pp ) ;
 ulong new_size = ( ulong ) pstype -> ssize * new_num_elements ;
 ulong old_size_rounded = obj_align_round ( old_size ) ;
 ulong new_size_rounded = obj_align_round ( new_size ) ;
 void * new_obj = NULL ;


 pp -> o_size = new_size ;
 new_obj = obj ;
 }
 else if ( imem -> cc && ( byte * ) obj + old_size_rounded == imem -> cc -> cbot && imem -> cc -> ctop - ( byte * ) obj >= new_size_rounded ) {
 imem -> cc -> cbot = ( byte * ) obj + new_size_rounded ;
 pp -> o_size = new_size ;
 new_obj = obj ;
 }
 else if ( new_size_rounded + sizeof ( obj_header_t ) <= old_size_rounded ) {
 trim_obj ( imem , obj , new_size , ( clump_t * ) 0 ) ;
 new_obj = obj ;
 }
 if ( new_obj ) {
 if_debug8m ( 'A' , mem , "[a%d:%c%c ]%s %s(%lu=>%lu) 0x%lx\n" , alloc_trace_space ( imem ) , ( new_size > old_size ? '>' : '<' ) , ( pstype == & st_bytes ? 'b' : '<' ) , client_name_string ( cname ) , struct_type_name_string ( pstype ) , old_size , new_size , ( ulong ) obj ) ;
 return new_obj ;
 }
 new_obj = gs_alloc_struct_array ( mem , new_num_elements , void , pstype , cname ) ;
 if ( new_obj == 0 ) return 0 ;
 memcpy ( new_obj , obj , min ( old_size , new_size ) ) ;
 gs_free_object ( mem , obj , cname ) ;
 return new_obj ;
 }