int event_loopexit ( const struct timeval * tv ) {
 return ( event_once ( - 1 , EV_TIMEOUT , event_loopexit_cb , current_base , tv ) ) ;
 }