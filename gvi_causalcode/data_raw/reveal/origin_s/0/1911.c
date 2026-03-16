static int zcountexecstack ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 push ( 1 ) ;
 make_int ( op , count_exec_stack ( i_ctx_p , false ) ) ;
 return 0 ;
 }