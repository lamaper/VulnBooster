static int zinstopped ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 uint count ;
 check_type ( * op , t_integer ) ;
 count = count_to_stopped ( i_ctx_p , op -> value . intval ) ;
 if ( count ) {
 push ( 1 ) ;
 op [ - 1 ] = * ref_stack_index ( & e_stack , count - 2 ) ;
 make_true ( op ) ;
 }
 else make_false ( op ) ;
 return 0 ;
 }