static void * ialloc_solo ( gs_memory_t * parent , gs_memory_type_ptr_t pstype , clump_t * * pcp ) {
 clump_t * cp = gs_raw_alloc_struct_immovable ( parent , & st_clump , "ialloc_solo(clump)" ) ;
 uint csize = ROUND_UP ( sizeof ( clump_head_t ) + sizeof ( obj_header_t ) + pstype -> ssize , obj_align_mod ) ;
 byte * cdata = gs_alloc_bytes_immovable ( parent , csize , "ialloc_solo" ) ;
 obj_header_t * obj = ( obj_header_t * ) ( cdata + sizeof ( clump_head_t ) ) ;
 if ( cp == 0 || cdata == 0 ) {
 gs_free_object ( parent , cp , "ialloc_solo(allocation failure)" ) ;
 gs_free_object ( parent , cdata , "ialloc_solo(allocation failure)" ) ;
 return 0 ;
 }
 alloc_init_clump ( cp , cdata , cdata + csize , false , ( clump_t * ) NULL ) ;
 cp -> cbot = cp -> ctop ;
 cp -> parent = cp -> left = cp -> right = 0 ;
 cp -> c_alone = true ;
 obj -> o_pad = 0 ;
 obj -> o_alone = 1 ;
 obj -> o_size = pstype -> ssize ;
 obj -> o_type = pstype ;
 * pcp = cp ;
 return ( void * ) ( obj + 1 ) ;
 }