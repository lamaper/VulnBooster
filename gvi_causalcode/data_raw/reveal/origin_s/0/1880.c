static mpa_state_t * init_mpa_state ( void ) {
 mpa_state_t * state ;
 state = ( mpa_state_t * ) wmem_alloc0 ( wmem_file_scope ( ) , sizeof ( mpa_state_t ) ) ;
 state -> revision = - 1 ;
 return state ;
 }