END_TEST START_TEST ( test_all_users_waiting_to_send ) {
 in_addr_t ip ;
 ip = inet_addr ( "127.0.0.1" ) ;
 init_users ( ip , 27 ) ;
 fail_unless ( all_users_waiting_to_send ( ) == 1 ) ;
 users [ 0 ] . conn = CONN_DNS_NULL ;
 users [ 0 ] . active = 1 ;
 fail_unless ( all_users_waiting_to_send ( ) == 1 ) ;
 users [ 0 ] . last_pkt = time ( NULL ) ;
 users [ 0 ] . outpacket . len = 0 ;
 fail_unless ( all_users_waiting_to_send ( ) == 0 ) ;



 }