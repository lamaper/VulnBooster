int zrepeat ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 check_proc ( * op ) ;
 check_type ( op [ - 1 ] , t_integer ) ;
 if ( op [ - 1 ] . value . intval < 0 ) return_error ( gs_error_rangecheck ) ;
 check_estack ( 5 ) ;
 push_mark_estack ( es_for , no_cleanup ) ;
 * ++ esp = op [ - 1 ] ;
 * ++ esp = * op ;
 make_op_estack ( esp + 1 , repeat_continue ) ;
 pop ( 2 ) ;
 return repeat_continue ( i_ctx_p ) ;
 }