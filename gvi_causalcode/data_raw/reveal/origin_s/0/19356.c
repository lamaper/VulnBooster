int zexec ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 int code ;
 check_op ( 1 ) ;
 code = check_for_exec ( op ) ;
 if ( code < 0 ) {
 return code ;
 }
 if ( ! r_has_attr ( op , a_executable ) ) {
 return 0 ;
 }
 check_estack ( 1 ) ;
 ++ esp ;
 ref_assign ( esp , op ) ;
 esfile_check_cache ( ) ;
 pop ( 1 ) ;
 return o_push_estack ;
 }