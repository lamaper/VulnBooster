static int for_samples_continue ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 es_ptr ep = esp ;
 int var = ep [ - 4 ] . value . intval ;
 float a = ep [ - 3 ] . value . realval ;
 int n = ep [ - 2 ] . value . intval ;
 float b = ep [ - 1 ] . value . realval ;
 if ( var > n ) {
 esp -= 6 ;
 return o_pop_estack ;
 }
 push ( 1 ) ;
 make_real ( op , ( ( n - var ) * a + var * b ) / n ) ;
 ep [ - 4 ] . value . intval = var + 1 ;
 ref_assign_inline ( ep + 2 , ep ) ;
 esp = ep + 2 ;
 return o_push_estack ;
 }