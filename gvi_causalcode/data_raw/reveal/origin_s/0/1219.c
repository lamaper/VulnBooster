static int zexecstack2 ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 check_type ( * op , t_boolean ) ;
 return push_execstack ( i_ctx_p , op - 1 , op -> value . boolval , execstack2_continue ) ;
 }