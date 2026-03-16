static int for_real_continue ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 es_ptr ep = esp ;
 float var = ep [ - 3 ] . value . realval ;
 float incr = ep [ - 2 ] . value . realval ;
 if ( incr >= 0 ? ( var > ep [ - 1 ] . value . realval ) : ( var < ep [ - 1 ] . value . realval ) ) {
 esp -= 5 ;
 return o_pop_estack ;
 }
 push ( 1 ) ;
 ref_assign ( op , ep - 3 ) ;
 ep [ - 3 ] . value . realval = var + incr ;
 esp = ep + 2 ;
 ref_assign ( ep + 2 , ep ) ;
 return o_push_estack ;
 }