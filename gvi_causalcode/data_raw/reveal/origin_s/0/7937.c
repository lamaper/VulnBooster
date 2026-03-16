static int remoteStreamFilter ( struct qemud_client * client , struct qemud_client_message * msg , void * opaque ) {
 struct qemud_client_stream * stream = opaque ;
 if ( msg -> hdr . serial == stream -> serial && msg -> hdr . proc == stream -> procedure && msg -> hdr . type == REMOTE_STREAM ) {
 VIR_DEBUG ( "Incoming rx=%p serial=%d proc=%d status=%d" , stream -> rx , msg -> hdr . proc , msg -> hdr . serial , msg -> hdr . status ) ;
 if ( stream -> rx ) {
 qemudClientMessageQueuePush ( & stream -> rx , msg ) ;
 remoteStreamUpdateEvents ( stream ) ;
 }
 else {
 int ret = 0 ;
 switch ( msg -> hdr . status ) {
 case REMOTE_OK : ret = remoteStreamHandleFinish ( client , stream , msg ) ;
 if ( ret == 0 ) qemudClientMessageRelease ( client , msg ) ;
 break ;
 case REMOTE_CONTINUE : qemudClientMessageQueuePush ( & stream -> rx , msg ) ;
 remoteStreamUpdateEvents ( stream ) ;
 break ;
 case REMOTE_ERROR : default : ret = remoteStreamHandleAbort ( client , stream , msg ) ;
 if ( ret == 0 ) qemudClientMessageRelease ( client , msg ) ;
 break ;
 }
 if ( ret < 0 ) return - 1 ;
 }
 return 1 ;
 }
 return 0 ;
 }