int ztokenexec ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 stream * s ;
 scanner_state state ;
 check_read_file ( i_ctx_p , s , op ) ;
 check_estack ( 1 ) ;
 gs_scanner_init ( & state , op ) ;
 return tokenexec_continue ( i_ctx_p , & state , true ) ;
 }