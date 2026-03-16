static int zexecstack ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 return push_execstack ( i_ctx_p , op , false , execstack_continue ) ;
 }