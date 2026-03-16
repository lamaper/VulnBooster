void event_queue_remove ( struct event_base * base , struct event * ev , int queue ) {
 if ( ! ( ev -> ev_flags & queue ) ) event_errx ( 1 , "%s: %p(fd %d) not on queue %x" , __func__ , ev , ev -> ev_fd , queue ) ;
 if ( ~ ev -> ev_flags & EVLIST_INTERNAL ) base -> event_count -- ;
 ev -> ev_flags &= ~ queue ;
 switch ( queue ) {
 case EVLIST_INSERTED : TAILQ_REMOVE ( & base -> eventqueue , ev , ev_next ) ;
 break ;
 case EVLIST_ACTIVE : base -> event_count_active -- ;
 TAILQ_REMOVE ( base -> activequeues [ ev -> ev_pri ] , ev , ev_active_next ) ;
 break ;
 case EVLIST_TIMEOUT : min_heap_erase ( & base -> timeheap , ev ) ;
 break ;
 default : event_errx ( 1 , "%s: unknown queue %x" , __func__ , queue ) ;
 }
 }