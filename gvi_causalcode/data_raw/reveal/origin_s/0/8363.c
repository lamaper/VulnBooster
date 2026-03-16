static int loop_continue ( i_ctx_t * i_ctx_p ) {
 register es_ptr ep = esp ;
 ref_assign ( ep + 2 , ep ) ;
 esp = ep + 2 ;
 return o_push_estack ;
 }