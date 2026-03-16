static int remoteStreamHandleAbort ( struct qemud_client * client , struct qemud_client_stream * stream , struct qemud_client_message * msg ) {
 remote_error rerr ;
 VIR_DEBUG ( "stream=%p proc=%d serial=%d" , stream , msg -> hdr . proc , msg -> hdr . serial ) ;
 memset ( & rerr , 0 , sizeof rerr ) ;
 stream -> closed = 1 ;
 virStreamEventRemoveCallback ( stream -> st ) ;
 virStreamAbort ( stream -> st ) ;
 if ( msg -> hdr . status == REMOTE_ERROR ) remoteDispatchFormatError ( & rerr , "%s" , _ ( "stream aborted at client request" ) ) ;
 else {
 VIR_WARN ( "unexpected stream status %d" , msg -> hdr . status ) ;
 remoteDispatchFormatError ( & rerr , _ ( "stream aborted with unexpected status %d" ) , msg -> hdr . status ) ;
 }
 return remoteSerializeReplyError ( client , & rerr , & msg -> hdr ) ;
 }