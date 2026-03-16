int remoteAddClientStream ( struct qemud_client * client , struct qemud_client_stream * stream , int transmit ) {
 struct qemud_client_stream * tmp = client -> streams ;
 VIR_DEBUG ( "client=%p proc=%d serial=%d" , client , stream -> procedure , stream -> serial ) ;
 if ( virStreamEventAddCallback ( stream -> st , 0 , remoteStreamEvent , client , NULL ) < 0 ) return - 1 ;
 if ( tmp ) {
 while ( tmp -> next ) tmp = tmp -> next ;
 tmp -> next = stream ;
 }
 else {
 client -> streams = stream ;
 }
 stream -> filter . next = client -> filters ;
 client -> filters = & stream -> filter ;
 if ( transmit ) stream -> tx = 1 ;
 remoteStreamUpdateEvents ( stream ) ;
 return 0 ;
 }