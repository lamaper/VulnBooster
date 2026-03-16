static int zstop ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 uint count = count_to_stopped ( i_ctx_p , 1L ) ;
 if ( count ) {
 check_ostack ( 2 ) ;
 pop_estack ( i_ctx_p , count ) ;
 op = osp ;
 push ( 1 ) ;
 make_true ( op ) ;
 return o_pop_estack ;
 }
 push ( 2 ) ;
 return unmatched_exit ( op , zstop ) ;
 }