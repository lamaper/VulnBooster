static void event_once_cb ( int fd , short events , void * arg ) {
 struct event_once * eonce = arg ;
 ( * eonce -> cb ) ( fd , events , eonce -> arg ) ;
 free ( eonce ) ;
 }