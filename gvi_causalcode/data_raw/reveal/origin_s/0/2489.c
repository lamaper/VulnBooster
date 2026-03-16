static int zquit ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 check_op ( 2 ) ;
 check_type ( * op , t_integer ) ;
 return_error ( gs_error_Quit ) ;
 }