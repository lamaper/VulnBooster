struct qemud_client_stream * remoteFindClientStream ( struct qemud_client * client , virStreamPtr st ) {
 struct qemud_client_stream * stream = client -> streams ;
 while ( stream ) {
 if ( stream -> st == st ) return stream ;
 stream = stream -> next ;
 }
 return NULL ;
 }