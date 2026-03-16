static int zzstop ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 uint count ;
 check_type ( * op , t_integer ) ;
 count = count_to_stopped ( i_ctx_p , op -> value . intval ) ;
 if ( count ) {
 ref save_result ;
 check_op ( 2 ) ;
 save_result = op [ - 1 ] ;
 pop ( 2 ) ;
 pop_estack ( i_ctx_p , count ) ;
 op = osp ;
 push ( 1 ) ;
 * op = save_result ;
 return o_pop_estack ;
 }
 return unmatched_exit ( op , zzstop ) ;
 }