static int repeat_continue ( i_ctx_t * i_ctx_p ) {
 es_ptr ep = esp ;
 if ( -- ( ep [ - 1 ] . value . intval ) >= 0 ) {
 esp += 2 ;
 ref_assign ( esp , ep ) ;
 return o_push_estack ;
 }
 else {
 esp -= 3 ;
 return o_pop_estack ;
 }
 }