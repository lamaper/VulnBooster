static int zloop ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 check_proc ( * op ) ;
 check_estack ( 4 ) ;
 push_mark_estack ( es_for , no_cleanup ) ;
 * ++ esp = * op ;
 make_op_estack ( esp + 1 , loop_continue ) ;
 pop ( 1 ) ;
 return loop_continue ( i_ctx_p ) ;
 }