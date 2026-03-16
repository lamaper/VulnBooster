static void remoteStreamUpdateEvents ( struct qemud_client_stream * stream ) {
 int newEvents = 0 ;
 if ( stream -> rx ) newEvents |= VIR_STREAM_EVENT_WRITABLE ;
 if ( stream -> tx && ! stream -> recvEOF ) newEvents |= VIR_STREAM_EVENT_READABLE ;
 virStreamEventUpdateCallback ( stream -> st , newEvents ) ;
 }