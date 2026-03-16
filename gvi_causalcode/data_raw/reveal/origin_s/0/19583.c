static struct search_state * search_state_new ( void ) {
 struct search_state * state = ( struct search_state * ) malloc ( sizeof ( struct search_state ) ) ;
 if ( ! state ) return NULL ;
 memset ( state , 0 , sizeof ( struct search_state ) ) ;
 state -> refcount = 1 ;
 state -> ndots = 1 ;
 return state ;
 }