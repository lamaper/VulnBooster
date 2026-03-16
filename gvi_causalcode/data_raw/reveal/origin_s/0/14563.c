static void rpc_test ( void ) {
 struct msg * msg , * msg2 ;
 struct kill * attack ;
 struct run * run ;
 struct evbuffer * tmp = evbuffer_new ( ) ;
 struct timeval tv_start , tv_end ;
 uint32_t tag ;
 int i ;
 fprintf ( stdout , "Testing RPC: " ) ;
 msg = msg_new ( ) ;
 EVTAG_ASSIGN ( msg , from_name , "niels" ) ;
 EVTAG_ASSIGN ( msg , to_name , "phoenix" ) ;
 if ( EVTAG_GET ( msg , attack , & attack ) == - 1 ) {
 fprintf ( stderr , "Failed to set kill message.\n" ) ;
 exit ( 1 ) ;
 }
 EVTAG_ASSIGN ( attack , weapon , "feather" ) ;
 EVTAG_ASSIGN ( attack , action , "tickle" ) ;
 evutil_gettimeofday ( & tv_start , NULL ) ;
 for ( i = 0 ;
 i < 1000 ;
 ++ i ) {
 run = EVTAG_ADD ( msg , run ) ;
 if ( run == NULL ) {
 fprintf ( stderr , "Failed to add run message.\n" ) ;
 exit ( 1 ) ;
 }
 EVTAG_ASSIGN ( run , how , "very fast but with some data in it" ) ;
 EVTAG_ASSIGN ( run , fixed_bytes , ( unsigned char * ) "012345678901234567890123" ) ;
 }
 if ( msg_complete ( msg ) == - 1 ) {
 fprintf ( stderr , "Failed to make complete message.\n" ) ;
 exit ( 1 ) ;
 }
 evtag_marshal_msg ( tmp , 0xdeaf , msg ) ;
 if ( evtag_peek ( tmp , & tag ) == - 1 ) {
 fprintf ( stderr , "Failed to peak tag.\n" ) ;
 exit ( 1 ) ;
 }
 if ( tag != 0xdeaf ) {
 fprintf ( stderr , "Got incorrect tag: %0x.\n" , tag ) ;
 exit ( 1 ) ;
 }
 msg2 = msg_new ( ) ;
 if ( evtag_unmarshal_msg ( tmp , 0xdeaf , msg2 ) == - 1 ) {
 fprintf ( stderr , "Failed to unmarshal message.\n" ) ;
 exit ( 1 ) ;
 }
 evutil_gettimeofday ( & tv_end , NULL ) ;
 evutil_timersub ( & tv_end , & tv_start , & tv_end ) ;
 fprintf ( stderr , "(%.1f us/add) " , ( float ) tv_end . tv_sec / ( float ) i * 1000000.0 + tv_end . tv_usec / ( float ) i ) ;
 if ( ! EVTAG_HAS ( msg2 , from_name ) || ! EVTAG_HAS ( msg2 , to_name ) || ! EVTAG_HAS ( msg2 , attack ) ) {
 fprintf ( stderr , "Missing data structures.\n" ) ;
 exit ( 1 ) ;
 }
 if ( EVTAG_LEN ( msg2 , run ) != i ) {
 fprintf ( stderr , "Wrong number of run messages.\n" ) ;
 exit ( 1 ) ;
 }
 msg_free ( msg ) ;
 msg_free ( msg2 ) ;
 evbuffer_free ( tmp ) ;
 fprintf ( stdout , "OK\n" ) ;
 }