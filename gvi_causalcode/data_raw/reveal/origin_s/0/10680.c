END_TEST START_TEST ( test_users_waiting ) {
 in_addr_t ip ;
 ip = inet_addr ( "127.0.0.1" ) ;
 init_users ( ip , 27 ) ;
 fail_unless ( users_waiting_on_reply ( ) == 0 ) ;
 users [ 3 ] . active = 1 ;
 fail_unless ( users_waiting_on_reply ( ) == 0 ) ;
 users [ 3 ] . last_pkt = time ( NULL ) ;
 fail_unless ( users_waiting_on_reply ( ) == 0 ) ;
 users [ 3 ] . conn = CONN_DNS_NULL ;
 users [ 3 ] . q . id = 1 ;
 fail_unless ( users_waiting_on_reply ( ) == 1 ) ;
 }