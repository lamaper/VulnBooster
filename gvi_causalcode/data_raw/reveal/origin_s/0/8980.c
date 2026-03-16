int remoteSendStreamData ( struct qemud_client * client , struct qemud_client_stream * stream , const char * data , unsigned int len ) {
 struct qemud_client_message * msg ;
 XDR xdr ;
 VIR_DEBUG ( "client=%p stream=%p data=%p len=%d" , client , stream , data , len ) ;
 if ( VIR_ALLOC ( msg ) < 0 ) {
 return - 1 ;
 }
 msg -> hdr . prog = REMOTE_PROGRAM ;
 msg -> hdr . vers = REMOTE_PROTOCOL_VERSION ;
 msg -> hdr . proc = stream -> procedure ;
 msg -> hdr . type = REMOTE_STREAM ;
 msg -> hdr . serial = stream -> serial ;
 msg -> hdr . status = data ? REMOTE_CONTINUE : REMOTE_OK ;
 if ( remoteEncodeClientMessageHeader ( msg ) < 0 ) goto fatal_error ;
 if ( data && len ) {
 if ( ( msg -> bufferLength - msg -> bufferOffset ) < len ) goto fatal_error ;
 xdrmem_create ( & xdr , msg -> buffer , msg -> bufferLength , XDR_ENCODE ) ;
 if ( xdr_setpos ( & xdr , msg -> bufferOffset ) == 0 ) goto xdr_error ;
 memcpy ( msg -> buffer + msg -> bufferOffset , data , len ) ;
 msg -> bufferOffset += len ;
 len = msg -> bufferOffset ;
 if ( xdr_setpos ( & xdr , 0 ) == 0 ) goto xdr_error ;
 if ( ! xdr_u_int ( & xdr , & len ) ) goto xdr_error ;
 xdr_destroy ( & xdr ) ;
 VIR_DEBUG ( "Total %d" , msg -> bufferOffset ) ;
 }
 if ( data ) msg -> streamTX = 1 ;
 msg -> bufferLength = msg -> bufferOffset ;
 msg -> bufferOffset = 0 ;
 qemudClientMessageQueuePush ( & client -> tx , msg ) ;
 qemudUpdateClientEvent ( client ) ;
 return 0 ;
 xdr_error : xdr_destroy ( & xdr ) ;
 fatal_error : VIR_FREE ( msg ) ;
 VIR_WARN ( "Failed to serialize stream data for proc %d as XDR" , stream -> procedure ) ;
 return - 1 ;
 }