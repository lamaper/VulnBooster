int event_base_loopexit ( struct event_base * event_base , const struct timeval * tv ) {
 return ( event_base_once ( event_base , - 1 , EV_TIMEOUT , event_loopexit_cb , event_base , tv ) ) ;
 }