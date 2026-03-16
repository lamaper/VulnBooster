void event_set ( struct event * ev , int fd , short events , void ( * callback ) ( int , short , void * ) , void * arg ) {
 ev -> ev_base = current_base ;
 ev -> ev_callback = callback ;
 ev -> ev_arg = arg ;
 ev -> ev_fd = fd ;
 ev -> ev_events = events ;
 ev -> ev_res = 0 ;
 ev -> ev_flags = EVLIST_INIT ;
 ev -> ev_ncalls = 0 ;
 ev -> ev_pncalls = NULL ;
 min_heap_elem_init ( ev ) ;
 if ( current_base ) ev -> ev_pri = current_base -> nactivequeues / 2 ;
 }