void pop_estack ( i_ctx_t * i_ctx_p , uint count ) {
 uint idx = 0 ;
 uint popped = 0 ;
 esfile_clear_cache ( ) ;
 for ( ;
 idx < count ;
 idx ++ ) {
 ref * ep = ref_stack_index ( & e_stack , idx - popped ) ;
 if ( r_is_estack_mark ( ep ) ) {
 ref_stack_pop ( & e_stack , idx + 1 - popped ) ;
 popped = idx + 1 ;
 ( * real_opproc ( ep ) ) ( i_ctx_p ) ;
 }
 }
 ref_stack_pop ( & e_stack , count - popped ) ;
 }