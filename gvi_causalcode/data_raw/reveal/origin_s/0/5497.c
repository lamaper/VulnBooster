int min_heap_elem_greater ( struct event * a , struct event * b ) {
 return evutil_timercmp ( & a -> ev_timeout , & b -> ev_timeout , > ) ;
 }