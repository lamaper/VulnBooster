static void i_free_object ( gs_memory_t * mem , void * ptr , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 obj_header_t * pp ;
 gs_memory_type_ptr_t pstype ;
 gs_memory_struct_type_t saved_stype ;
 struct_proc_finalize ( ( * finalize ) ) ;
 uint size , rounded_size ;
 if ( ptr == 0 ) return ;
 pp = ( obj_header_t * ) ptr - 1 ;
 pstype = pp -> o_type ;

 clump_locator_t cld ;
 if ( pstype == & st_free ) {
 mlprintf2 ( mem , "%s: object 0x%lx already free!\n" , client_name_string ( cname ) , ( ulong ) ptr ) ;
 return ;
 }
 cld . memory = imem ;
 while ( ( cld . cp = cld . memory -> root ) , ! clump_locate_ptr ( ptr , & cld ) ) {
 if ( ! cld . memory -> saved ) {
 mlprintf3 ( mem , "%s: freeing 0x%lx, not owned by memory 0x%lx!\n" , client_name_string ( cname ) , ( ulong ) ptr , ( ulong ) mem ) ;
 return ;
 }
 cld . memory = ( gs_ref_memory_t * ) cld . memory -> saved ;
 }
 if ( ! ( PTR_BETWEEN ( ( const byte * ) pp , cld . cp -> cbase , cld . cp -> cbot ) ) ) {
 mlprintf5 ( mem , "%s: freeing 0x%lx,\n\toutside clump 0x%lx cbase=0x%lx, cbot=0x%lx!\n" , client_name_string ( cname ) , ( ulong ) ptr , ( ulong ) cld . cp , ( ulong ) cld . cp -> cbase , ( ulong ) cld . cp -> cbot ) ;
 return ;
 }
 }

 rounded_size = obj_align_round ( size ) ;
 finalize = pstype -> finalize ;
 if ( finalize != 0 ) {
 if ( gs_debug [ 'a' ] || gs_debug [ 'A' ] ) saved_stype = * pstype ;
 if_debug3m ( 'u' , mem , "[u]finalizing %s 0x%lx (%s)\n" , struct_type_name_string ( pstype ) , ( ulong ) ptr , client_name_string ( cname ) ) ;
 ( * finalize ) ( mem , ptr ) ;
 if ( gs_debug [ 'a' ] || gs_debug [ 'A' ] ) pstype = & saved_stype ;
 }
 if ( imem -> cc && ( byte * ) ptr + rounded_size == imem -> cc -> cbot ) {
 alloc_trace ( ":-o " , imem , cname , pstype , size , ptr ) ;
 gs_alloc_fill ( ptr , gs_alloc_fill_free , size ) ;
 imem -> cc -> cbot = ( byte * ) pp ;
 if ( ( byte * ) pp <= imem -> cc -> int_freed_top ) {
 consolidate_clump_free ( imem -> cc , imem ) ;
 }
 return ;
 }
 if ( pp -> o_alone ) {
 clump_locator_t cl ;

 clump_locator_t cld ;
 cld . memory = imem ;
 cld . cp = 0 ;
 if ( gs_debug_c ( 'a' ) ) alloc_trace ( ( clump_locate_ptr ( ptr , & cld ) ? ":-oL" : ":-o~" ) , imem , cname , pstype , size , ptr ) ;
 }

 cl . cp = 0 ;
 if ( clump_locate_ptr ( ptr , & cl ) ) {
 if ( ! imem -> is_controlled ) alloc_free_clump ( cl . cp , imem ) ;
 return ;
 }
 }
 if ( rounded_size >= sizeof ( obj_header_t * ) ) {
 imem -> cfreed . memory = imem ;
 if ( clump_locate ( ptr , & imem -> cfreed ) ) {
 obj_header_t * * pfl ;
 if ( size > max_freelist_size ) {
 pfl = & imem -> freelists [ LARGE_FREELIST_INDEX ] ;
 if ( rounded_size > imem -> largest_free_size ) imem -> largest_free_size = rounded_size ;
 }
 else {
 pfl = & imem -> freelists [ ( size + obj_align_mask ) >> log2_obj_align_mod ] ;
 }
 if ( imem -> cc && imem -> cfreed . cp -> chead == imem -> cc -> chead ) {
 if ( ( byte * ) pp >= imem -> cc -> int_freed_top ) {
 imem -> cc -> int_freed_top = ( byte * ) ptr + rounded_size ;
 }
 }
 else {
 if ( ( byte * ) pp >= imem -> cfreed . cp -> int_freed_top ) {
 imem -> cfreed . cp -> int_freed_top = ( byte * ) ptr + rounded_size ;
 }
 }
 pp -> o_type = & st_free ;
 o_set_unmarked ( pp ) ;
 gs_alloc_fill ( ptr , gs_alloc_fill_free , size ) ;
 * ( obj_header_t * * ) ptr = * pfl ;
 * pfl = ( obj_header_t * ) ptr ;
 alloc_trace ( ( size > max_freelist_size ? ":-oF" : ":-of" ) , imem , cname , pstype , size , ptr ) ;
 return ;
 }
 }
 else {
 pp -> o_type = & st_free ;
 gs_alloc_fill ( ptr , gs_alloc_fill_free , size ) ;
 }
 alloc_trace ( ":-o#" , imem , cname , pstype , size , ptr ) ;
 imem -> lost . objects += obj_size_round ( size ) ;
 }