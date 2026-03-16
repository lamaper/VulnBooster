static int err_end_runandhide ( i_ctx_t * i_ctx_p ) {
 int code ;
 if ( ( code = runandhide_restore_hidden ( i_ctx_p , esp + 3 , esp + 2 ) ) < 0 ) return code ;
 return 0 ;
 }