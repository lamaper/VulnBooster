static void nameserver_prod_callback ( int fd , short events , void * arg ) {
 struct nameserver * const ns = ( struct nameserver * ) arg ;
 ( void ) fd ;
 ( void ) events ;
 nameserver_send_probe ( ns ) ;
 }