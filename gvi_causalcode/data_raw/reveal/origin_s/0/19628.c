static obj_header_t * alloc_obj ( gs_ref_memory_t * mem , ulong lsize , gs_memory_type_ptr_t pstype , alloc_flags_t flags , client_name_t cname ) {
 obj_header_t * ptr ;
 if ( lsize >= mem -> large_size || ( flags & ALLOC_IMMOVABLE ) ) {
 ulong asize = ( ( lsize + obj_align_mask ) & - obj_align_mod ) + sizeof ( obj_header_t ) ;
 clump_t * cp = alloc_acquire_clump ( mem , asize + sizeof ( clump_head_t ) , false , "large object clump" ) ;
 if ( # if ARCH_SIZEOF_LONG > ARCH_SIZEOF_INT asize > max_uint # else asize < lsize # endif ) return 0 ;
 if ( cp == 0 ) return 0 ;
 cp -> c_alone = true ;
 ptr = ( obj_header_t * ) cp -> cbot ;
 cp -> cbot += asize ;
 ptr -> o_pad = 0 ;
 ptr -> o_alone = 1 ;
 ptr -> o_size = lsize ;
 }
 else {
 clump_splay_walker sw ;
 clump_t * cp = clump_splay_walk_init_mid ( & sw , mem -> cc ) ;
 uint asize = obj_size_round ( ( uint ) lsize ) ;
 bool allocate_success = false ;
 if ( lsize > max_freelist_size && ( flags & ALLOC_DIRECT ) ) {
 if ( ( ptr = large_freelist_alloc ( mem , lsize ) ) != 0 ) {
 -- ptr ;
 goto done ;
 }
 }
 if ( cp == 0 ) {
 mem -> cc = clump_splay_walk_init ( & sw , mem ) ;
 alloc_open_clump ( mem ) ;
 }

 if ( CAN_ALLOC_AT_END ( mem -> cc ) ) {
 allocate_success = true ;
 break ;
 }
 else if ( mem -> is_controlled ) {
 gs_consolidate_free ( ( gs_memory_t * ) mem ) ;
 if ( CAN_ALLOC_AT_END ( mem -> cc ) ) {
 allocate_success = true ;
 break ;
 }
 }
 cp = clump_splay_walk_fwd ( & sw ) ;
 if ( cp == NULL ) break ;
 alloc_close_clump ( mem ) ;
 mem -> cc = cp ;
 alloc_open_clump ( mem ) ;
 }
 while ( 1 ) ;

 if ( ! mem -> is_controlled ) {
 clump_t * cp ;
 alloc_close_clump ( mem ) ;
 for ( cp = clump_splay_walk_init_mid ( & sw , cp_orig ) ;
 cp != NULL ;
 cp = clump_splay_walk_fwd ( & sw ) ) {
 consolidate_clump_free ( cp , mem ) ;
 if ( CAN_ALLOC_AT_END ( cp ) ) {
 mem -> cc = cp ;
 alloc_open_clump ( mem ) ;
 allocate_success = true ;
 break ;
 }
 }
 }
 }

 clump_t * cp = alloc_add_clump ( mem , ( ulong ) mem -> clump_size , "clump" ) ;
 if ( cp ) {
 ptr = ( obj_header_t * ) cp -> cbot ;
 allocate_success = true ;
 }
 }
 if ( allocate_success ) mem -> cc -> cbot = ( byte * ) ptr + asize ;
 else if ( ! mem -> is_controlled || ( ptr = scavenge_low_free ( mem , ( uint ) lsize ) ) == 0 ) return 0 ;
 ptr -> o_pad = 0 ;
 ptr -> o_alone = 0 ;
 ptr -> o_size = ( uint ) lsize ;
 }
 done : ptr -> o_type = pstype ;


 ASSIGN_HDR_ID ( ptr ) ;
 gs_alloc_fill ( ptr , gs_alloc_fill_alloc , lsize ) ;
 return ptr ;
 }
 static void consolidate_clump_free ( clump_t * cp , gs_ref_memory_t * mem ) {
 obj_header_t * begin_free = 0 ;
 cp -> int_freed_top = cp -> cbase ;
 SCAN_CLUMP_OBJECTS ( cp ) DO_ALL if ( pre -> o_type == & st_free ) {
 if ( begin_free == 0 ) begin_free = pre ;
 }
 else {
 if ( begin_free ) cp -> int_freed_top = ( byte * ) pre ;
 begin_free = 0 ;
 }
 END_OBJECTS_SCAN if ( begin_free ) {
 remove_range_from_freelist ( mem , begin_free , cp -> cbot ) ;
 if_debug4m ( 'a' , ( const gs_memory_t * ) mem , "[a]resetting clump 0x%lx cbot from 0x%lx to 0x%lx (%lu free)\n" , ( ulong ) cp , ( ulong ) cp -> cbot , ( ulong ) begin_free , ( ulong ) ( ( byte * ) cp -> cbot - ( byte * ) begin_free ) ) ;
 cp -> cbot = ( byte * ) begin_free ;
 }
 }
 static splay_app_result_t consolidate ( clump_t * cp , void * arg ) {
 gs_ref_memory_t * mem = ( gs_ref_memory_t * ) arg ;
 consolidate_clump_free ( cp , mem ) ;
 if ( cp -> cbot == cp -> cbase && cp -> ctop == cp -> climit ) {
 if ( ! mem -> is_controlled ) {
 alloc_free_clump ( cp , mem ) ;
 if ( mem -> cc == cp ) mem -> cc = NULL ;
 }
 }
 return SPLAY_APP_CONTINUE ;
 }
 void ialloc_consolidate_free ( gs_ref_memory_t * mem ) {
 alloc_close_clump ( mem ) ;
 clump_splay_app ( mem -> root , mem , consolidate , mem ) ;
 if ( mem -> cc == NULL ) mem -> cc = mem -> root ;
 alloc_open_clump ( mem ) ;
 }
 static void i_consolidate_free ( gs_memory_t * mem ) {
 ialloc_consolidate_free ( ( gs_ref_memory_t * ) mem ) ;
 }
 typedef struct {
 uint need_free ;
 obj_header_t * found_pre ;
 gs_ref_memory_t * mem ;
 unsigned request_size ;
 }
 scavenge_data ;
 static splay_app_result_t scavenge ( clump_t * cp , void * arg ) {
 scavenge_data * sd = ( scavenge_data * ) arg ;
 obj_header_t * begin_free = NULL ;
 uint found_free = 0 ;
 sd -> found_pre = NULL ;
 SCAN_CLUMP_OBJECTS ( cp ) DO_ALL if ( pre -> o_type == & st_free ) {
 if ( begin_free == 0 ) {
 found_free = 0 ;
 begin_free = pre ;
 }
 found_free += pre_obj_rounded_size ( pre ) ;
 if ( begin_free != 0 && found_free >= sd -> need_free ) break ;
 }
 else begin_free = 0 ;
 END_OBJECTS_SCAN_NO_ABORT if ( begin_free != 0 && found_free >= sd -> need_free ) {
 remove_range_from_freelist ( sd -> mem , ( char * ) begin_free , ( char * ) begin_free + found_free ) ;
 sd -> found_pre = begin_free ;
 sd -> found_pre -> o_type = & st_free ;
 sd -> found_pre -> o_size = found_free - sizeof ( obj_header_t ) ;
 trim_obj ( sd -> mem , sd -> found_pre + 1 , sd -> request_size , cp ) ;
 return SPLAY_APP_STOP ;
 }
 return SPLAY_APP_CONTINUE ;
 }
 static obj_header_t * scavenge_low_free ( gs_ref_memory_t * mem , unsigned request_size ) {
 scavenge_data sd ;
 uint request_size_rounded = obj_size_round ( request_size ) ;
 sd . found_pre = 0 ;
 sd . need_free = request_size_rounded + sizeof ( obj_header_t ) ;
 sd . mem = mem ;
 sd . request_size = request_size ;
 clump_splay_app ( mem -> root , mem , scavenge , & sd ) ;
 return sd . found_pre ;
 }
 static void remove_range_from_freelist ( gs_ref_memory_t * mem , void * bottom , void * top ) {
 int num_free [ num_freelists ] ;
 int smallest = num_freelists , largest = - 1 ;
 const obj_header_t * cur ;
 uint size ;
 int i ;
 uint removed = 0 ;
 for ( cur = bottom ;
 cur != top ;
 cur = ( const obj_header_t * ) ( ( const byte * ) cur + obj_size_round ( size ) ) ) {
 size = cur -> o_size ;
 i = ( size > max_freelist_size ? LARGE_FREELIST_INDEX : ( size + obj_align_mask ) >> log2_obj_align_mod ) ;
 if ( i < smallest ) {
 if ( i == 0 ) continue ;
 if ( smallest < num_freelists ) memset ( & num_free [ i ] , 0 , ( smallest - i ) * sizeof ( int ) ) ;
 else num_free [ i ] = 0 ;
 smallest = i ;
 }
 if ( i > largest ) {
 if ( largest >= 0 ) memset ( & num_free [ largest + 1 ] , 0 , ( i - largest ) * sizeof ( int ) ) ;
 largest = i ;
 }
 num_free [ i ] ++ ;
 }
 for ( i = smallest ;
 i <= largest ;
 i ++ ) {
 int count = num_free [ i ] ;
 obj_header_t * pfree ;
 obj_header_t * * ppfprev ;
 if ( ! count ) continue ;
 ppfprev = & mem -> freelists [ i ] ;
 for ( ;
 ;
 ) {
 pfree = * ppfprev ;
 if ( PTR_GE ( pfree , bottom ) && PTR_LT ( pfree , top ) ) {
 * ppfprev = * ( obj_header_t * * ) pfree ;
 removed += obj_align_round ( pfree [ - 1 ] . o_size ) ;
 if ( ! -- count ) break ;
 }
 else ppfprev = ( obj_header_t * * ) pfree ;
 }
 }
 mem -> lost . objects -= ( char * ) top - ( char * ) bottom - removed ;
 }
 static void trim_obj ( gs_ref_memory_t * mem , obj_header_t * obj , uint size , clump_t * cp ) {
 uint rounded_size = obj_align_round ( size ) ;
 obj_header_t * pre_obj = obj - 1 ;
 obj_header_t * excess_pre = ( obj_header_t * ) ( ( char * ) obj + rounded_size ) ;
 uint old_rounded_size = obj_align_round ( pre_obj -> o_size ) ;
 uint excess_size = old_rounded_size - rounded_size - sizeof ( obj_header_t ) ;
 pre_obj -> o_size = size ;
 if ( old_rounded_size == rounded_size ) return ;
 if ( pre_obj -> o_alone ) {
 if ( ! cp ) {
 mem -> cfreed . memory = mem ;
 if ( clump_locate ( obj , & mem -> cfreed ) ) {
 cp = mem -> cfreed . cp ;
 }
 }
 if ( cp ) {

 lprintf3 ( "resizing 0x%lx, old size %u, new size %u, cbot wrong!\n" , ( ulong ) obj , old_rounded_size , size ) ;
 }
 else # endif {
 cp -> cbot = ( byte * ) excess_pre ;
 return ;
 }
 }
 pre_obj -> o_pad = 0 ;
 pre_obj -> o_alone = 0 ;
 }
 excess_pre -> o_type = & st_free ;
 excess_pre -> o_size = excess_size ;
 excess_pre -> o_pad = 0 ;
 excess_pre -> o_alone = 0 ;
 if ( excess_size >= obj_align_mod ) {
 obj_header_t * * pfl ;
 if ( mem -> cc && ( byte * ) excess_pre >= mem -> cc -> int_freed_top ) mem -> cc -> int_freed_top = ( byte * ) excess_pre + excess_size ;
 if ( excess_size <= max_freelist_size ) pfl = & mem -> freelists [ ( excess_size + obj_align_mask ) >> log2_obj_align_mod ] ;
 else {
 uint rounded_size = obj_align_round ( excess_size ) ;
 pfl = & mem -> freelists [ LARGE_FREELIST_INDEX ] ;
 if ( rounded_size > mem -> largest_free_size ) mem -> largest_free_size = rounded_size ;
 }
 * ( obj_header_t * * ) ( excess_pre + 1 ) = * pfl ;
 * pfl = excess_pre + 1 ;
 mem -> cfreed . memory = mem ;
 }
 else {
 mem -> lost . objects += excess_size + sizeof ( obj_header_t ) ;
 }
 }
 static int i_register_root ( gs_memory_t * mem , gs_gc_root_t * rp , gs_ptr_type_t ptype , void * * up , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 if ( rp == NULL ) {
 rp = gs_raw_alloc_struct_immovable ( imem -> non_gc_memory , & st_gc_root_t , "i_register_root" ) ;
 if ( rp == 0 ) return_error ( gs_error_VMerror ) ;
 rp -> free_on_unregister = true ;
 }
 else rp -> free_on_unregister = false ;
 if_debug3m ( '8' , mem , "[8]register root(%s) 0x%lx -> 0x%lx\n" , client_name_string ( cname ) , ( ulong ) rp , ( ulong ) up ) ;
 rp -> ptype = ptype ;
 rp -> p = up ;
 rp -> next = imem -> roots ;
 imem -> roots = rp ;
 return 0 ;
 }
 static void i_unregister_root ( gs_memory_t * mem , gs_gc_root_t * rp , client_name_t cname ) {
 gs_ref_memory_t * const imem = ( gs_ref_memory_t * ) mem ;
 gs_gc_root_t * * rpp = & imem -> roots ;
 if_debug2m ( '8' , mem , "[8]unregister root(%s) 0x%lx\n" , client_name_string ( cname ) , ( ulong ) rp ) ;
 while ( * rpp != rp ) rpp = & ( * rpp ) -> next ;
 * rpp = ( * rpp ) -> next ;
 if ( rp -> free_on_unregister ) gs_free_object ( imem -> non_gc_memory , rp , "i_unregister_root" ) ;
 }
 public_st_clump ( ) ;
 void alloc_link_clump ( clump_t * cp , gs_ref_memory_t * imem ) {
 splay_insert ( cp , imem ) ;
 SANITY_CHECK ( cp ) ;
 }
 static clump_t * alloc_add_clump ( gs_ref_memory_t * mem , ulong csize , client_name_t cname ) {
 clump_t * cp = alloc_acquire_clump ( mem , csize , true , cname ) ;
 if ( cp ) {
 alloc_close_clump ( mem ) ;
 mem -> cc = cp ;
 gs_alloc_fill ( mem -> cc -> cbase , gs_alloc_fill_free , mem -> cc -> climit - mem -> cc -> cbase ) ;
 }
 return cp ;
 }
 static clump_t * alloc_acquire_clump ( gs_ref_memory_t * mem , ulong csize , bool has_strings , client_name_t cname ) {
 gs_memory_t * parent = mem -> non_gc_memory ;
 clump_t * cp ;
 byte * cdata ;


 if ( mem -> gc_status . signal_value != 0 ) {
 if ( ( ulong ) ( mem -> allocated ) >= mem -> limit ) {
 mem -> gc_status . requested += csize ;
 if ( mem -> limit >= mem -> gc_status . max_vm ) {
 gs_free_object ( parent , cp , cname ) ;
 return 0 ;
 }
 if_debug4m ( '0' , ( const gs_memory_t * ) mem , "[0]signaling space=%d, allocated=%ld, limit=%ld, requested=%ld\n" , mem -> space , ( long ) mem -> allocated , ( long ) mem -> limit , ( long ) mem -> gc_status . requested ) ;
 mem -> gs_lib_ctx -> gcsignal = mem -> gc_status . signal_value ;
 }
 }
 cdata = gs_alloc_bytes_immovable ( parent , csize , cname ) ;
 if ( cp == 0 || cdata == 0 ) {
 gs_free_object ( parent , cdata , cname ) ;
 gs_free_object ( parent , cp , cname ) ;
 mem -> gc_status . requested = csize ;
 return 0 ;
 }
 alloc_init_clump ( cp , cdata , cdata + csize , has_strings , ( clump_t * ) 0 ) ;
 alloc_link_clump ( cp , mem ) ;
 mem -> allocated += st_clump . ssize + csize ;
 SANITY_CHECK ( cp ) ;
 return cp ;
 }
 void alloc_init_clump ( clump_t * cp , byte * bot , byte * top , bool has_strings , clump_t * outer ) {
 byte * cdata = bot ;
 if ( outer != 0 ) outer -> inner_count ++ ;
 cp -> chead = ( clump_head_t * ) cdata ;
 cdata += sizeof ( clump_head_t ) ;
 cp -> cbot = cp -> cbase = cp -> int_freed_top = cdata ;
 cp -> cend = top ;
 cp -> rcur = 0 ;
 cp -> rtop = 0 ;
 cp -> outer = outer ;
 cp -> inner_count = 0 ;
 cp -> has_refs = false ;
 cp -> sbase = cdata ;
 cp -> c_alone = false ;
 if ( has_strings && top - cdata >= string_space_quantum + sizeof ( long ) - 1 ) {
 uint nquanta = string_space_quanta ( top - cdata ) ;
 cp -> climit = cdata + nquanta * string_data_quantum ;
 cp -> smark = cp -> climit ;
 cp -> smark_size = string_quanta_mark_size ( nquanta ) ;
 cp -> sreloc = ( string_reloc_offset * ) ( cp -> smark + cp -> smark_size ) ;
 cp -> sfree1 = ( uint * ) cp -> sreloc ;
 }
 else {
 cp -> climit = cp -> cend ;
 cp -> sfree1 = 0 ;
 cp -> smark = 0 ;
 cp -> smark_size = 0 ;
 cp -> sreloc = 0 ;
 }
 cp -> ctop = cp -> climit ;
 alloc_init_free_strings ( cp ) ;
 }
 void alloc_init_free_strings ( clump_t * cp ) {
 if ( cp -> sfree1 ) memset ( cp -> sfree1 , 0 , STRING_FREELIST_SPACE ( cp ) ) ;
 cp -> sfree = 0 ;
 }
 void alloc_close_clump ( gs_ref_memory_t * mem ) {

 dmlprintf1 ( ( const gs_memory_t * ) mem , "[a%d]" , alloc_trace_space ( mem ) ) ;
 dmprintf_clump ( ( const gs_memory_t * ) mem , "closing clump" , mem -> cc ) ;
 }

 void alloc_open_clump ( gs_ref_memory_t * mem ) {

 dmlprintf1 ( ( const gs_memory_t * ) mem , "[a%d]" , alloc_trace_space ( mem ) ) ;
 dmprintf_clump ( ( const gs_memory_t * ) mem , "opening clump" , mem -> cc ) ;
 }


 clump_t * * cpp = ( clump_t * * ) arg ;
 if ( * cpp != cp ) return SPLAY_APP_CONTINUE ;
 * cpp = NULL ;
 return SPLAY_APP_STOP ;
 }

 SANITY_CHECK_MID ( cp ) ;

 clump_t * found = cp ;
 clump_splay_app ( mem -> root , mem , check_in_clump , & found ) ;
 if ( found != NULL ) {
 mlprintf2 ( ( const gs_memory_t * ) mem , "unlink_clump 0x%lx not owned by memory 0x%lx!\n" , ( ulong ) cp , ( ulong ) mem ) ;
 return ;
 }
 }

 if ( mem -> cc == cp ) {
 mem -> cc = NULL ;
 }
 }
 void alloc_free_clump ( clump_t * cp , gs_ref_memory_t * mem ) {
 gs_memory_t * parent = mem -> non_gc_memory ;
 byte * cdata = ( byte * ) cp -> chead ;
 ulong csize = ( byte * ) cp -> cend - cdata ;
 alloc_unlink_clump ( cp , mem ) ;
 mem -> allocated -= st_clump . ssize ;
 if ( mem -> cfreed . cp == cp ) mem -> cfreed . cp = 0 ;
 if ( cp -> outer == 0 ) {
 mem -> allocated -= csize ;
 gs_free_object ( parent , cdata , "alloc_free_clump(data)" ) ;
 }
 else {
 cp -> outer -> inner_count -- ;
 gs_alloc_fill ( cdata , gs_alloc_fill_free , csize ) ;
 }
 gs_free_object ( parent , cp , "alloc_free_clump(clump struct)" ) ;
 }
 bool clump_locate_ptr ( const void * ptr , clump_locator_t * clp ) {
 clump_t * cp = clp -> memory -> root ;
 while ( cp ) {
 if ( PTR_LT ( ptr , cp -> cbase ) ) {
 cp = cp -> left ;
 continue ;
 }
 if ( PTR_GE ( ptr , cp -> cend ) ) {
 cp = cp -> right ;
 continue ;
 }
 splay_move_to_root ( cp , clp -> memory ) ;
 clp -> cp = cp ;
 return ! ptr_is_in_inner_clump ( ptr , cp ) ;
 }
 return false ;
 }
 bool ptr_is_within_mem_clumps ( const void * ptr , gs_ref_memory_t * mem ) {
 clump_t * cp = mem -> root ;
 while ( cp ) {
 if ( PTR_LT ( ptr , cp -> cbase ) ) {
 cp = cp -> left ;
 continue ;
 }
 if ( PTR_GE ( ptr , cp -> cend ) ) {
 cp = cp -> right ;
 continue ;
 }
 splay_move_to_root ( cp , mem ) ;
 return true ;
 }
 return false ;
 }

 return ( ( pdc -> bottom == NULL || PTR_GT ( otop , pdc -> bottom ) ) && ( pdc -> top == NULL || PTR_LT ( obot , pdc -> top ) ) ) ;
 }
 const dump_control_t dump_control_default = {
 dump_do_default , NULL , NULL }
 ;
 const dump_control_t dump_control_all = {
 dump_do_strings | dump_do_type_addresses | dump_do_pointers | dump_do_pointed_strings | dump_do_contents , NULL , NULL }
 ;
 const dump_control_t dump_control_no_contents = {
 dump_do_strings | dump_do_type_addresses | dump_do_pointers | dump_do_pointed_strings , NULL , NULL }
 ;
 static void debug_indent ( const gs_memory_t * mem , int indent ) {
 int i ;
 for ( i = indent ;
 i > 0 ;
 -- i ) dmputc ( mem , ' ' ) ;
 }
 static void debug_dump_contents ( const gs_memory_t * mem , const byte * bot , const byte * top , int indent , bool as_chars ) {
 const byte * block ;

 for ( block = bot - ( ( bot - ( byte * ) 0 ) & ( block_size - 1 ) ) ;
 block < top ;
 block += block_size ) {
 int i ;
 char label [ 12 ] ;
 if ( block >= bot + block_size && block <= top - ( block_size * 2 ) && ! memcmp ( block , block - block_size , block_size ) && ! memcmp ( block , block + block_size , block_size ) ) {
 if ( block < bot + block_size * 2 || memcmp ( block , block - block_size * 2 , block_size ) ) {
 debug_indent ( mem , indent ) ;
 dmputs ( mem , " ...\n" ) ;
 }
 continue ;
 }
 gs_sprintf ( label , "0x%lx:" , ( ulong ) block ) ;
 debug_indent ( mem , indent ) ;
 dmputs ( mem , label ) ;
 for ( i = 0 ;
 i < block_size ;
 ++ i ) {
 const char * sepr = ( ( i & 3 ) == 0 && i != 0 ? " " : " " ) ;
 dmputs ( mem , sepr ) ;
 if ( block + i >= bot && block + i < top ) dmprintf1 ( mem , "%02x" , block [ i ] ) ;
 else dmputs ( mem , " " ) ;
 }
 dmputc ( mem , '\n' ) ;
 if ( as_chars ) {
 debug_indent ( mem , indent + strlen ( label ) ) ;
 for ( i = 0 ;
 i < block_size ;
 ++ i ) {
 byte ch ;
 if ( ( i & 3 ) == 0 && i != 0 ) dmputc ( mem , ' ' ) ;
 if ( block + i >= bot && block + i < top && ( ch = block [ i ] ) >= 32 && ch <= 126 ) dmprintf1 ( mem , " %c" , ch ) ;
 else dmputs ( mem , " " ) ;
 }
 dmputc ( mem , '\n' ) ;
 }
 }

 void debug_print_object ( const gs_memory_t * mem , const void * obj , const dump_control_t * control ) {
 const obj_header_t * pre = ( ( const obj_header_t * ) obj ) - 1 ;
 ulong size = pre_obj_contents_size ( pre ) ;
 const gs_memory_struct_type_t * type = pre -> o_type ;
 dump_options_t options = control -> options ;
 dmprintf3 ( mem , " pre=0x%lx(obj=0x%lx) size=%lu" , ( ulong ) pre , ( ulong ) obj , size ) ;
 switch ( options & ( dump_do_type_addresses | dump_do_no_types ) ) {
 case dump_do_type_addresses + dump_do_no_types : dmprintf1 ( mem , " type=0x%lx" , ( ulong ) type ) ;
 break ;
 case dump_do_type_addresses : dmprintf2 ( mem , " type=%s(0x%lx)" , struct_type_name_string ( type ) , ( ulong ) type ) ;
 break ;
 case 0 : dmprintf1 ( mem , " type=%s" , struct_type_name_string ( type ) ) ;
 case dump_do_no_types : ;
 }
 if ( options & dump_do_marks ) {
 dmprintf2 ( mem , " smark/back=%u (0x%x)" , pre -> o_smark , pre -> o_smark ) ;
 }
 dmputc ( mem , '\n' ) ;
 if ( type == & st_free ) return ;
 if ( options & dump_do_pointers ) {
 struct_proc_enum_ptrs ( ( * proc ) ) = type -> enum_ptrs ;
 uint index = 0 ;
 enum_ptr_t eptr ;
 gs_ptr_type_t ptype ;
 if ( proc != gs_no_struct_enum_ptrs ) {
 if ( proc != 0 ) {
 for ( ;
 ( ptype = ( * proc ) ( mem , pre + 1 , size , index , & eptr , type , NULL ) ) != 0 ;
 ++ index ) {
 const void * ptr = eptr . ptr ;
 dmprintf1 ( mem , " ptr %u: " , index ) ;
 if ( ptype == ptr_string_type || ptype == ptr_const_string_type ) {
 const gs_const_string * str = ( const gs_const_string * ) & eptr ;
 if ( ! str ) dmprintf ( mem , "0x0" ) ;
 else dmprintf2 ( mem , "0x%lx(%u)" , ( ulong ) str -> data , str -> size ) ;
 if ( options & dump_do_pointed_strings ) {
 dmputs ( mem , " =>\n" ) ;
 if ( ! str ) dmprintf ( mem , "(null)\n" ) ;
 else debug_dump_contents ( mem , str -> data , str -> data + str -> size , 6 , true ) ;
 }
 else {
 dmputc ( mem , '\n' ) ;
 }
 }
 else {
 dmprintf1 ( mem , ( PTR_BETWEEN ( ptr , obj , ( const byte * ) obj + size ) ? "(0x%lx)\n" : "0x%lx\n" ) , ( ulong ) ptr ) ;
 }
 }
 }
 else {
 dmprintf ( mem , "previous line should be a ref\n" ) ;
 }
 }
 }
 if ( options & dump_do_contents ) {
 debug_dump_contents ( mem , ( const byte * ) obj , ( const byte * ) obj + size , 0 , false ) ;
 }
 }
 void debug_dump_clump ( const gs_memory_t * mem , const clump_t * cp , const dump_control_t * control ) {
 dmprintf1 ( mem , "clump at 0x%lx:\n" , ( ulong ) cp ) ;
 dmprintf3 ( mem , " chead=0x%lx cbase=0x%lx sbase=0x%lx\n" , ( ulong ) cp -> chead , ( ulong ) cp -> cbase , ( ulong ) cp -> sbase ) ;
 dmprintf3 ( mem , " rcur=0x%lx rtop=0x%lx cbot=0x%lx\n" , ( ulong ) cp -> rcur , ( ulong ) cp -> rtop , ( ulong ) cp -> cbot ) ;
 dmprintf4 ( mem , " ctop=0x%lx climit=0x%lx smark=0x%lx, size=%u\n" , ( ulong ) cp -> ctop , ( ulong ) cp -> climit , ( ulong ) cp -> smark , cp -> smark_size ) ;
 dmprintf2 ( mem , " sreloc=0x%lx cend=0x%lx\n" , ( ulong ) cp -> sreloc , ( ulong ) cp -> cend ) ;
 dmprintf6 ( mem , "left=0x%lx right=0x%lx parent=0x%lx outer=0x%lx inner_count=%u has_refs=%s\n" , ( ulong ) cp -> left , ( ulong ) cp -> right , ( ulong ) cp -> parent , ( ulong ) cp -> outer , cp -> inner_count , ( cp -> has_refs ? "true" : "false" ) ) ;
 dmprintf2 ( mem , " sfree1=0x%lx sfree=0x%x\n" , ( ulong ) cp -> sfree1 , cp -> sfree ) ;
 if ( control -> options & dump_do_strings ) {
 debug_dump_contents ( mem , ( control -> bottom == 0 ? cp -> ctop : max ( control -> bottom , cp -> ctop ) ) , ( control -> top == 0 ? cp -> climit : min ( control -> top , cp -> climit ) ) , 0 , true ) ;
 }
 SCAN_CLUMP_OBJECTS ( cp ) DO_ALL if ( obj_in_control_region ( pre + 1 , ( const byte * ) ( pre + 1 ) + size , control ) ) debug_print_object ( mem , pre + 1 , control ) ;
 END_OBJECTS_SCAN_NO_ABORT }
 void debug_print_clump ( const gs_memory_t * mem , const clump_t * cp ) {
 dump_control_t control ;
 control = dump_control_default ;
 debug_dump_clump ( mem , cp , & control ) ;
 }
 void debug_dump_memory ( const gs_ref_memory_t * mem , const dump_control_t * control ) {
 const clump_t * cp ;
 clump_splay_walker sw ;
 for ( cp = clump_splay_walk_init ( & sw , mem ) ;
 cp != NULL ;
 cp = clump_splay_walk_fwd ( & sw ) ) {
 if ( obj_in_control_region ( cp -> cbase , cp -> cend , control ) ) debug_dump_clump ( ( const gs_memory_t * ) mem , cp , control ) ;
 }
 }
 void debug_dump_allocator ( const gs_ref_memory_t * mem ) {
 debug_dump_memory ( mem , & dump_control_no_contents ) ;
 }
 void debug_find_pointers ( const gs_ref_memory_t * mem , const void * target ) {
 clump_splay_walker sw ;
 dump_control_t control ;
 const clump_t * cp ;
 control . options = 0 ;
 for ( cp = clump_splay_walk_init ( & sw , mem ) ;
 cp ;
 cp = clump_splay_walk_fwd ( & sw ) ) {
 SCAN_CLUMP_OBJECTS ( cp ) ;
 DO_ALL struct_proc_enum_ptrs ( ( * proc ) ) = pre -> o_type -> enum_ptrs ;
 uint index = 0 ;
 enum_ptr_t eptr ;
 if ( proc ) for ( ;
 ( * proc ) ( ( const gs_memory_t * ) mem , pre + 1 , size , index , & eptr , pre -> o_type , NULL ) ;
 ++ index ) if ( eptr . ptr == target ) {
 dmprintf1 ( ( const gs_memory_t * ) mem , "Index %d in" , index ) ;
 debug_print_object ( ( const gs_memory_t * ) mem , pre + 1 , & control ) ;
 }
 END_OBJECTS_SCAN_NO_ABORT }
 }
 static void ddct ( const gs_memory_t * mem , clump_t * cp , clump_t * parent , int depth ) {
 int i ;
 if ( cp == NULL ) return ;
 for ( i = 0 ;
 i < depth ;
 i ++ ) dmlprintf ( mem , " " ) ;
 dmlprintf7 ( mem , "Clump %p:%p parent=%p left=%p:%p right=%p:%p\n" , cp , cp -> cbase , cp -> parent , cp -> left , cp -> left ? cp -> left -> cbase : NULL , cp -> right , cp -> right ? cp -> right -> cbase : NULL ) ;
 if ( cp -> parent != parent ) dmlprintf ( mem , "Parent pointer mismatch!\n" ) ;
 ddct ( mem , cp -> left , cp , depth + 1 ) ;
 ddct ( mem , cp -> right , cp , depth + 1 ) ;
 }
 void debug_dump_clump_tree ( const gs_ref_memory_t * mem ) {
 ddct ( ( const gs_memory_t * ) mem , mem -> root , NULL , 0 ) ;
 }
