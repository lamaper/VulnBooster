static byte * i_alloc_string ( gs_memory_t * mem , uint nbytes , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 byte * str ;
 clump_splay_walker sw ;
 clump_t * cp = clump_splay_walk_init_mid ( & sw , imem -> cc ) ;
 if ( nbytes + ( uint ) HDR_ID_OFFSET < nbytes ) return NULL ;
 nbytes += HDR_ID_OFFSET ;


 imem -> cc = clump_splay_walk_init ( & sw , imem ) ;
 alloc_open_clump ( imem ) ;
 }
 top : if ( imem -> cc && imem -> cc -> ctop - imem -> cc -> cbot > nbytes ) {
 if_debug4m ( 'A' , mem , "[a%d:+> ]%s(%u) = 0x%lx\n" , alloc_trace_space ( imem ) , client_name_string ( cname ) , nbytes , ( ulong ) ( imem -> cc -> ctop - nbytes ) ) ;
 str = imem -> cc -> ctop -= nbytes ;
 gs_alloc_fill ( str , gs_alloc_fill_alloc , nbytes ) ;
 str += HDR_ID_OFFSET ;
 ASSIGN_HDR_ID ( str ) ;
 return str ;
 }
 cp = clump_splay_walk_fwd ( & sw ) ;
 if ( cp != NULL ) {
 alloc_close_clump ( imem ) ;
 imem -> cc = cp ;
 alloc_open_clump ( imem ) ;
 goto top ;
 }
 if ( nbytes > string_space_quanta ( max_uint - sizeof ( clump_head_t ) ) * string_data_quantum ) {
 return 0 ;
 }
 if ( nbytes >= imem -> large_size ) {
 return i_alloc_string_immovable ( mem , nbytes , cname ) ;
 }
 else {
 cp = alloc_acquire_clump ( imem , ( ulong ) imem -> clump_size , true , "clump" ) ;
 if ( cp == 0 ) return 0 ;
 alloc_close_clump ( imem ) ;
 imem -> cc = clump_splay_walk_init_mid ( & sw , cp ) ;
 gs_alloc_fill ( imem -> cc -> cbase , gs_alloc_fill_free , imem -> cc -> climit - imem -> cc -> cbase ) ;
 goto top ;
 }
 }