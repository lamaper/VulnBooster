START_TEST ( test_init_users ) {
 in_addr_t ip ;
 char givenip [ 16 ] ;
 int i ;
 int count ;
 ip = inet_addr ( "127.0.0.1" ) ;
 count = init_users ( ip , 27 ) ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 fail_unless ( users [ i ] . id == i ) ;
 fail_unless ( users [ i ] . q . id == 0 ) ;
 fail_unless ( users [ i ] . inpacket . len == 0 ) ;
 fail_unless ( users [ i ] . outpacket . len == 0 ) ;
 snprintf ( givenip , sizeof ( givenip ) , "127.0.0.%d" , i + 2 ) ;
 fail_unless ( users [ i ] . tun_ip == inet_addr ( givenip ) ) ;
 }
 }