static int remoteStreamHandleWrite ( struct qemud_client * client , struct qemud_client_stream * stream ) {
 struct qemud_client_message * msg , * tmp ;
 VIR_DEBUG ( "stream=%p" , stream ) ;
 msg = stream -> rx ;
 while ( msg && ! stream -> closed ) {
 int ret ;
 switch ( msg -> hdr . status ) {
 case REMOTE_OK : ret = remoteStreamHandleFinish ( client , stream , msg ) ;
 break ;
 case REMOTE_CONTINUE : ret = remoteStreamHandleWriteData ( client , stream , msg ) ;
 break ;
 case REMOTE_ERROR : default : ret = remoteStreamHandleAbort ( client , stream , msg ) ;
 break ;
 }
 if ( ret == 0 ) qemudClientMessageQueueServe ( & stream -> rx ) ;
 else if ( ret < 0 ) return - 1 ;
 else break ;
 tmp = msg -> next ;
 qemudClientMessageRelease ( client , msg ) ;
 msg = tmp ;
 }
 return 0 ;
 }