static ref * zget_current_file ( i_ctx_t * i_ctx_p ) {
 ref_stack_enum_t rsenum ;
 ref_stack_enum_begin ( & rsenum , & e_stack ) ;
 do {
 uint count = rsenum . size ;
 es_ptr ep = rsenum . ptr + count - 1 ;
 for ( ;
 count ;
 count -- , ep -- ) if ( r_has_type_attrs ( ep , t_file , a_executable ) ) return ep ;
 }
 while ( ref_stack_enum_next ( & rsenum ) ) ;
 return 0 ;
 }