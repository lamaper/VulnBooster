static void evtag_fuzz ( void ) {
 u_char buffer [ 4096 ] ;
 struct evbuffer * tmp = evbuffer_new ( ) ;
 struct timeval tv ;
 int i , j ;
 int not_failed = 0 ;
 for ( j = 0 ;
 j < 100 ;
 j ++ ) {
 for ( i = 0 ;
 i < sizeof ( buffer ) ;
 i ++ ) buffer [ i ] = rand ( ) ;
 evbuffer_drain ( tmp , - 1 ) ;
 evbuffer_add ( tmp , buffer , sizeof ( buffer ) ) ;
 if ( evtag_unmarshal_timeval ( tmp , 0 , & tv ) != - 1 ) not_failed ++ ;
 }
 if ( not_failed >= 10 ) {
 fprintf ( stderr , "evtag_unmarshal should have failed" ) ;
 exit ( 1 ) ;
 }
 evbuffer_drain ( tmp , - 1 ) ;
 evutil_timerclear ( & tv ) ;
 tv . tv_sec = 1 ;
 evtag_marshal_timeval ( tmp , 0 , & tv ) ;
 evbuffer_add ( tmp , buffer , sizeof ( buffer ) ) ;
 EVBUFFER_DATA ( tmp ) [ 1 ] = 0xff ;
 if ( evtag_unmarshal_timeval ( tmp , 0 , & tv ) != - 1 ) {
 fprintf ( stderr , "evtag_unmarshal_timeval should have failed" ) ;
 exit ( 1 ) ;
 }
 evbuffer_free ( tmp ) ;
 fprintf ( stdout , "\t%s: OK\n" , __func__ ) ;
 }