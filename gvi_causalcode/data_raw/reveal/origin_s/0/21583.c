static int zrunandhide ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 es_ptr ep ;
 check_op ( 2 ) ;
 if ( ! r_is_array ( op - 1 ) ) return_op_typecheck ( op ) ;
 if ( ! r_has_attr ( op , a_executable ) ) return 0 ;
 check_estack ( 5 ) ;
 ep = esp += 5 ;
 make_mark_estack ( ep - 4 , es_other , err_end_runandhide ) ;
 make_op_estack ( ep - 1 , end_runandhide ) ;
 ref_assign ( ep , op ) ;
 make_int ( ep - 3 , ( int ) op [ - 1 ] . tas . type_attrs ) ;
 ref_assign ( ep - 2 , op - 1 ) ;
 r_clear_attrs ( ep - 2 , a_all ) ;
 esfile_check_cache ( ) ;
 pop ( 2 ) ;
 return o_push_estack ;
 }