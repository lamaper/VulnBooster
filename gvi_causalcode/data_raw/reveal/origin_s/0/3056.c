static int zcond ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 es_ptr ep = esp ;
 if ( ! r_is_array ( op ) ) return_op_typecheck ( op ) ;
 check_execute ( * op ) ;
 if ( ( r_size ( op ) & 1 ) != 0 ) return_error ( gs_error_rangecheck ) ;
 if ( r_size ( op ) == 0 ) return zpop ( i_ctx_p ) ;
 check_estack ( 3 ) ;
 esp = ep += 3 ;
 ref_assign ( ep - 2 , op ) ;
 make_op_estack ( ep - 1 , cond_continue ) ;
 array_get ( imemory , op , 0L , ep ) ;
 esfile_check_cache ( ) ;
 pop ( 1 ) ;
 return o_push_estack ;
 }