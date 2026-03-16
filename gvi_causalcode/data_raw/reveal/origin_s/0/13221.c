static int zzstopped ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 check_type ( * op , t_integer ) ;
 check_op ( 3 ) ;
 check_estack ( 5 ) ;
 push_mark_estack ( es_stopped , no_cleanup ) ;
 * ++ esp = op [ - 1 ] ;
 * ++ esp = * op ;
 push_op_estack ( stopped_push ) ;
 push_op_estack ( zexec ) ;
 pop ( 2 ) ;
 return o_push_estack ;
 }