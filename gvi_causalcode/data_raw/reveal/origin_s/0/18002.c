static byte * i_resize_string ( gs_memory_t * mem , byte * data , uint old_num , uint new_num , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 byte * ptr ;
 if ( old_num == new_num ) return data ;
 data -= HDR_ID_OFFSET ;
 old_num += HDR_ID_OFFSET ;
 new_num += HDR_ID_OFFSET ;
 if ( imem -> cc && data == imem -> cc -> ctop && ( new_num < old_num || imem -> cc -> ctop - imem -> cc -> cbot > new_num - old_num ) ) {
 ptr = data + old_num - new_num ;
 if_debug6m ( 'A' , mem , "[a%d:%c> ]%s(%u->%u) 0x%lx\n" , alloc_trace_space ( imem ) , ( new_num > old_num ? '>' : '<' ) , client_name_string ( cname ) , old_num , new_num , ( ulong ) ptr ) ;
 imem -> cc -> ctop = ptr ;
 memmove ( ptr , data , min ( old_num , new_num ) ) ;

 else gs_alloc_fill ( data , gs_alloc_fill_free , old_num - new_num ) ;

 ASSIGN_HDR_ID ( ptr ) ;
 }
 else if ( new_num < old_num ) {
 ptr = data ;
 imem -> lost . strings += old_num - new_num ;
 gs_alloc_fill ( data + new_num , gs_alloc_fill_free , old_num - new_num ) ;
 if_debug5m ( 'A' , mem , "[a%d:<> ]%s(%u->%u) 0x%lx\n" , alloc_trace_space ( imem ) , client_name_string ( cname ) , old_num , new_num , ( ulong ) ptr ) ;
 ptr += HDR_ID_OFFSET ;
 ASSIGN_HDR_ID ( ptr ) ;
 }
 else {
 data += HDR_ID_OFFSET ;
 old_num -= HDR_ID_OFFSET ;
 new_num -= HDR_ID_OFFSET ;
 ptr = gs_alloc_string ( mem , new_num , cname ) ;
 if ( ptr == 0 ) return 0 ;
 memcpy ( ptr , data , min ( old_num , new_num ) ) ;
 gs_free_string ( mem , data , old_num , cname ) ;
 }
 return ptr ;
 }