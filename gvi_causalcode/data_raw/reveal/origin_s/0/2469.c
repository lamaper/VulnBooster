static void nameserver_ready_callback ( int fd , short events , void * arg ) {
 struct nameserver * ns = ( struct nameserver * ) arg ;
 ( void ) fd ;
 if ( events & EV_WRITE ) {
 ns -> choked = 0 ;
 if ( ! evdns_transmit ( ) ) {
 nameserver_write_waiting ( ns , 0 ) ;
 }
 }
 if ( events & EV_READ ) {
 nameserver_read ( ns ) ;
 }
 }