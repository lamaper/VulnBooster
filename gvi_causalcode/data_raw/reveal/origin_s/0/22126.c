static int zexit ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 ref_stack_enum_t rsenum ;
 uint scanned = 0 ;
 ref_stack_enum_begin ( & rsenum , & e_stack ) ;
 do {
 uint used = rsenum . size ;
 es_ptr ep = rsenum . ptr + used - 1 ;
 uint count = used ;
 for ( ;
 count ;
 count -- , ep -- ) if ( r_is_estack_mark ( ep ) ) switch ( estack_mark_index ( ep ) ) {
 case es_for : pop_estack ( i_ctx_p , scanned + ( used - count + 1 ) ) ;
 return o_pop_estack ;
 case es_stopped : return_error ( gs_error_invalidexit ) ;
 }
 scanned += used ;
 }
 while ( ref_stack_enum_next ( & rsenum ) ) ;
 push ( 2 ) ;
 return unmatched_exit ( op , zexit ) ;
 }