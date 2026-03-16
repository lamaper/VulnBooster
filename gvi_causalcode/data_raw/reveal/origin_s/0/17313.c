int zif ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 check_proc ( * op ) ;
 check_type ( op [ - 1 ] , t_boolean ) ;
 if ( op [ - 1 ] . value . boolval ) {
 check_estack ( 1 ) ;
 ++ esp ;
 ref_assign ( esp , op ) ;
 esfile_check_cache ( ) ;
 }
 pop ( 2 ) ;
 return o_push_estack ;
 }