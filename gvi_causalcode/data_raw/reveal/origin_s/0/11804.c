int remoteDispatchClientRequest ( struct qemud_server * server , struct qemud_client * client , struct qemud_client_message * msg ) {
 int ret ;
 remote_error rerr ;
 bool qemu_call ;
 VIR_DEBUG ( "prog=%d ver=%d type=%d status=%d serial=%d proc=%d" , msg -> hdr . prog , msg -> hdr . vers , msg -> hdr . type , msg -> hdr . status , msg -> hdr . serial , msg -> hdr . proc ) ;
 memset ( & rerr , 0 , sizeof rerr ) ;
 if ( msg -> hdr . prog == REMOTE_PROGRAM ) qemu_call = false ;
 else if ( msg -> hdr . prog == QEMU_PROGRAM ) qemu_call = true ;
 else {
 remoteDispatchFormatError ( & rerr , _ ( "program mismatch (actual %x, expected %x or %x)" ) , msg -> hdr . prog , REMOTE_PROGRAM , QEMU_PROGRAM ) ;
 goto error ;
 }
 if ( ! qemu_call && msg -> hdr . vers != REMOTE_PROTOCOL_VERSION ) {
 remoteDispatchFormatError ( & rerr , _ ( "version mismatch (actual %x, expected %x)" ) , msg -> hdr . vers , REMOTE_PROTOCOL_VERSION ) ;
 goto error ;
 }
 else if ( qemu_call && msg -> hdr . vers != QEMU_PROTOCOL_VERSION ) {
 remoteDispatchFormatError ( & rerr , _ ( "version mismatch (actual %x, expected %x)" ) , msg -> hdr . vers , QEMU_PROTOCOL_VERSION ) ;
 goto error ;
 }
 switch ( msg -> hdr . type ) {
 case REMOTE_CALL : return remoteDispatchClientCall ( server , client , msg , qemu_call ) ;
 case REMOTE_STREAM : VIR_INFO ( "Ignoring unexpected stream data serial=%d proc=%d status=%d" , msg -> hdr . serial , msg -> hdr . proc , msg -> hdr . status ) ;
 qemudClientMessageRelease ( client , msg ) ;
 break ;
 default : remoteDispatchFormatError ( & rerr , _ ( "type (%d) != REMOTE_CALL" ) , ( int ) msg -> hdr . type ) ;
 goto error ;
 }
 return 0 ;
 error : ret = remoteSerializeReplyError ( client , & rerr , & msg -> hdr ) ;
 if ( ret >= 0 ) VIR_FREE ( msg ) ;
 return ret ;
 }