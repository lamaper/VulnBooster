void event_base_free ( struct event_base * base ) {
 int i , n_deleted = 0 ;
 struct event * ev ;
 if ( base == NULL && current_base ) base = current_base ;
 if ( base == current_base ) current_base = NULL ;
 assert ( base ) ;
 for ( ev = TAILQ_FIRST ( & base -> eventqueue ) ;
 ev ;
 ) {
 struct event * next = TAILQ_NEXT ( ev , ev_next ) ;
 if ( ! ( ev -> ev_flags & EVLIST_INTERNAL ) ) {
 event_del ( ev ) ;
 ++ n_deleted ;
 }
 ev = next ;
 }
 while ( ( ev = min_heap_top ( & base -> timeheap ) ) != NULL ) {
 event_del ( ev ) ;
 ++ n_deleted ;
 }
 for ( i = 0 ;
 i < base -> nactivequeues ;
 ++ i ) {
 for ( ev = TAILQ_FIRST ( base -> activequeues [ i ] ) ;
 ev ;
 ) {
 struct event * next = TAILQ_NEXT ( ev , ev_active_next ) ;
 if ( ! ( ev -> ev_flags & EVLIST_INTERNAL ) ) {
 event_del ( ev ) ;
 ++ n_deleted ;
 }
 ev = next ;
 }
 }
 if ( n_deleted ) event_debug ( ( "%s: %d events were still set in base" , __func__ , n_deleted ) ) ;
 if ( base -> evsel -> dealloc != NULL ) base -> evsel -> dealloc ( base , base -> evbase ) ;
 for ( i = 0 ;
 i < base -> nactivequeues ;
 ++ i ) assert ( TAILQ_EMPTY ( base -> activequeues [ i ] ) ) ;
 assert ( min_heap_empty ( & base -> timeheap ) ) ;
 min_heap_dtor ( & base -> timeheap ) ;
 for ( i = 0 ;
 i < base -> nactivequeues ;
 ++ i ) free ( base -> activequeues [ i ] ) ;
 free ( base -> activequeues ) ;
 assert ( TAILQ_EMPTY ( & base -> eventqueue ) ) ;
 free ( base ) ;
 }