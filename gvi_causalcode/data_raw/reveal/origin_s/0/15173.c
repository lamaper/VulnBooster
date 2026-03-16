static void nameserver_probe_callback ( int result , char type , int count , int ttl , void * addresses , void * arg ) {
 struct nameserver * const ns = ( struct nameserver * ) arg ;
 ( void ) type ;
 ( void ) count ;
 ( void ) ttl ;
 ( void ) addresses ;
 if ( result == DNS_ERR_NONE || result == DNS_ERR_NOTEXIST ) {
 nameserver_up ( ns ) ;
 }
 else nameserver_probe_failed ( ns ) ;
 }