int zfor ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 register es_ptr ep ;
 int code ;
 float params [ 3 ] ;
 if ( ( code = float_params ( op - 1 , 3 , params ) ) < 0 ) return code ;
 if ( params [ 0 ] == 0.0 && params [ 1 ] == 0.0 ) {
 pop ( 4 ) ;
 return 0 ;
 }
 check_estack ( 7 ) ;
 ep = esp + 6 ;
 check_proc ( * op ) ;
 if ( r_has_type ( op - 3 , t_integer ) && r_has_type ( op - 2 , t_integer ) ) {
 make_int ( ep - 4 , op [ - 3 ] . value . intval ) ;
 make_int ( ep - 3 , op [ - 2 ] . value . intval ) ;
 switch ( r_type ( op - 1 ) ) {
 case t_integer : make_int ( ep - 2 , op [ - 1 ] . value . intval ) ;
 break ;
 case t_real : make_int ( ep - 2 , ( long ) op [ - 1 ] . value . realval ) ;
 break ;
 default : return_op_typecheck ( op - 1 ) ;
 }
 if ( ep [ - 3 ] . value . intval >= 0 ) make_op_estack ( ep , for_pos_int_continue ) ;
 else make_op_estack ( ep , for_neg_int_continue ) ;
 }
 else {
 make_real ( ep - 4 , params [ 0 ] ) ;
 make_real ( ep - 3 , params [ 1 ] ) ;
 make_real ( ep - 2 , params [ 2 ] ) ;
 make_op_estack ( ep , for_real_continue ) ;
 }
 make_mark_estack ( ep - 5 , es_for , no_cleanup ) ;
 ref_assign ( ep - 1 , op ) ;
 esp = ep ;
 pop ( 4 ) ;
 return o_push_estack ;
 }