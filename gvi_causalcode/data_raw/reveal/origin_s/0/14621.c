static int zstopped ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 check_op ( 1 ) ;
 check_estack ( 5 ) ;
 push_mark_estack ( es_stopped , no_cleanup ) ;
 ++ esp ;
 make_false ( esp ) ;
 ++ esp ;
 make_int ( esp , 1 ) ;
 push_op_estack ( stopped_push ) ;
 push_op_estack ( zexec ) ;
 return o_push_estack ;
 }