int zfor_samples ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 es_ptr ep ;
 check_type ( op [ - 3 ] , t_real ) ;
 check_type ( op [ - 2 ] , t_integer ) ;
 check_type ( op [ - 1 ] , t_real ) ;
 check_proc ( * op ) ;
 check_estack ( 8 ) ;
 ep = esp + 7 ;
 make_mark_estack ( ep - 6 , es_for , no_cleanup ) ;
 make_int ( ep - 5 , 0 ) ;
 memcpy ( ep - 4 , op - 3 , 3 * sizeof ( ref ) ) ;
 ref_assign ( ep - 1 , op ) ;
 make_op_estack ( ep , for_samples_continue ) ;
 esp = ep ;
 pop ( 4 ) ;
 return o_push_estack ;
 }