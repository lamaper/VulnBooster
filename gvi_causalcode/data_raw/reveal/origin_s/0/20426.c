static void i_free_string ( gs_memory_t * mem , byte * data , uint nbytes , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 if ( data ) {
 data -= HDR_ID_OFFSET ;
 nbytes += HDR_ID_OFFSET ;
 if ( imem -> cc && data == imem -> cc -> ctop ) {
 if_debug4m ( 'A' , mem , "[a%d:-> ]%s(%u) 0x%lx\n" , alloc_trace_space ( imem ) , client_name_string ( cname ) , nbytes , ( ulong ) data ) ;
 imem -> cc -> ctop += nbytes ;
 }
 else {
 if_debug4m ( 'A' , mem , "[a%d:->#]%s(%u) 0x%lx\n" , alloc_trace_space ( imem ) , client_name_string ( cname ) , nbytes , ( ulong ) data ) ;
 imem -> lost . strings += nbytes ;
 }
 gs_alloc_fill ( data , gs_alloc_fill_free , nbytes ) ;
 }
 }