int event_once ( int fd , short events , void ( * callback ) ( int , short , void * ) , void * arg , const struct timeval * tv ) {
 return event_base_once ( current_base , fd , events , callback , arg , tv ) ;
 }