void remoteStreamMessageFinished ( struct qemud_client * client , struct qemud_client_message * msg ) {
 struct qemud_client_stream * stream = client -> streams ;
 while ( stream ) {
 if ( msg -> hdr . proc == stream -> procedure && msg -> hdr . serial == stream -> serial ) break ;
 stream = stream -> next ;
 }
 VIR_DEBUG ( "Message client=%p stream=%p proc=%d serial=%d" , client , stream , msg -> hdr . proc , msg -> hdr . serial ) ;
 if ( stream ) {
 stream -> tx = 1 ;
 remoteStreamUpdateEvents ( stream ) ;
 }
 }