static int for_pos_int_continue ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 register es_ptr ep = esp ;
 int var = ep [ - 3 ] . value . intval ;
 if ( var > ep [ - 1 ] . value . intval ) {
 esp -= 5 ;
 return o_pop_estack ;
 }
 push ( 1 ) ;
 make_int ( op , var ) ;
 ep [ - 3 ] . value . intval = var + ep [ - 2 ] . value . intval ;
 ref_assign_inline ( ep + 2 , ep ) ;
 esp = ep + 2 ;
 return o_push_estack ;
 }