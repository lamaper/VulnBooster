static byte * i_alloc_string_immovable ( gs_memory_t * mem , uint nbytes , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 byte * str ;
 uint asize ;
 clump_t * cp ;
 nbytes += HDR_ID_OFFSET ;


 cp = alloc_acquire_clump ( imem , ( ulong ) asize , true , "large string clump" ) ;
 if ( cp == 0 ) return 0 ;
 cp -> c_alone = true ;
 str = cp -> ctop = cp -> climit - nbytes ;
 if_debug4m ( 'a' , mem , "[a%d|+>L]%s(%u) = 0x%lx\n" , alloc_trace_space ( imem ) , client_name_string ( cname ) , nbytes , ( ulong ) str ) ;
 gs_alloc_fill ( str , gs_alloc_fill_alloc , nbytes ) ;
 str += HDR_ID_OFFSET ;
 ASSIGN_HDR_ID ( str ) ;
 return str ;
 }