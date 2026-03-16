static int end_runandhide ( i_ctx_t * i_ctx_p ) {
 int code ;
 if ( ( code = runandhide_restore_hidden ( i_ctx_p , esp , esp - 1 ) ) < 0 ) {
 esp -= 2 ;
 return code ;
 }
 esp -= 2 ;
 return o_pop_estack ;
 }