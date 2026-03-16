static void event_process_active ( struct event_base * base ) {
 struct event * ev ;
 struct event_list * activeq = NULL ;
 int i ;
 short ncalls ;
 for ( i = 0 ;
 i < base -> nactivequeues ;
 ++ i ) {
 if ( TAILQ_FIRST ( base -> activequeues [ i ] ) != NULL ) {
 activeq = base -> activequeues [ i ] ;
 break ;
 }
 }
 assert ( activeq != NULL ) ;
 for ( ev = TAILQ_FIRST ( activeq ) ;
 ev ;
 ev = TAILQ_FIRST ( activeq ) ) {
 if ( ev -> ev_events & EV_PERSIST ) event_queue_remove ( base , ev , EVLIST_ACTIVE ) ;
 else event_del ( ev ) ;
 ncalls = ev -> ev_ncalls ;
 ev -> ev_pncalls = & ncalls ;
 while ( ncalls ) {
 ncalls -- ;
 ev -> ev_ncalls = ncalls ;
 ( * ev -> ev_callback ) ( ( int ) ev -> ev_fd , ev -> ev_res , ev -> ev_arg ) ;
 if ( event_gotsig || base -> event_break ) return ;
 }
 }
 }