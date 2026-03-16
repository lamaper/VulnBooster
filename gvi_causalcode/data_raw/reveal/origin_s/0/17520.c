int zifelse ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 check_proc ( * op ) ;
 check_proc ( op [ - 1 ] ) ;
 check_type ( op [ - 2 ] , t_boolean ) ;
 check_estack ( 1 ) ;
 ++ esp ;
 if ( op [ - 2 ] . value . boolval ) {
 ref_assign ( esp , op - 1 ) ;
 }
 else {
 ref_assign ( esp , op ) ;
 }
 esfile_check_cache ( ) ;
 pop ( 3 ) ;
 return o_push_estack ;
 }