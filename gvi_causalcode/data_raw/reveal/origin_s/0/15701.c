static int zcountexecstack1 ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 check_type ( * op , t_boolean ) ;
 make_int ( op , count_exec_stack ( i_ctx_p , op -> value . boolval ) ) ;
 return 0 ;
 }