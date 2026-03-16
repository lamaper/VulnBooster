static int stopped_push ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 push ( 1 ) ;
 * op = esp [ - 1 ] ;
 esp -= 3 ;
 return o_pop_estack ;
 }