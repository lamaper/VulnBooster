static int remoteDispatchClientCall ( struct qemud_server * server , struct qemud_client * client , struct qemud_client_message * msg , bool qemu_protocol ) {
 XDR xdr ;
 remote_error rerr ;
 dispatch_args args ;
 dispatch_ret ret ;
 const dispatch_data * data = NULL ;
 int rv = - 1 ;
 unsigned int len ;
 virConnectPtr conn = NULL ;
 memset ( & args , 0 , sizeof args ) ;
 memset ( & ret , 0 , sizeof ret ) ;
 memset ( & rerr , 0 , sizeof rerr ) ;
 if ( msg -> hdr . status != REMOTE_OK ) {
 remoteDispatchFormatError ( & rerr , _ ( "status (%d) != REMOTE_OK" ) , ( int ) msg -> hdr . status ) ;
 goto rpc_error ;
 }
 if ( client -> auth ) {
 if ( msg -> hdr . proc != REMOTE_PROC_AUTH_LIST && msg -> hdr . proc != REMOTE_PROC_AUTH_SASL_INIT && msg -> hdr . proc != REMOTE_PROC_AUTH_SASL_START && msg -> hdr . proc != REMOTE_PROC_AUTH_SASL_STEP && msg -> hdr . proc != REMOTE_PROC_AUTH_POLKIT ) {
 remoteDispatchFormatError ( & rerr , "%s" , _ ( "authentication required" ) ) ;
 goto rpc_error ;
 }
 }
 if ( qemu_protocol ) data = qemuGetDispatchData ( msg -> hdr . proc ) ;
 else data = remoteGetDispatchData ( msg -> hdr . proc ) ;
 if ( ! data ) {
 remoteDispatchFormatError ( & rerr , _ ( "unknown procedure: %d" ) , msg -> hdr . proc ) ;
 goto rpc_error ;
 }
 xdrmem_create ( & xdr , msg -> buffer + msg -> bufferOffset , msg -> bufferLength - msg -> bufferOffset , XDR_DECODE ) ;
 if ( ! ( ( data -> args_filter ) ( & xdr , & args ) ) ) {
 xdr_destroy ( & xdr ) ;
 remoteDispatchFormatError ( & rerr , "%s" , _ ( "parse args failed" ) ) ;
 goto rpc_error ;
 }
 xdr_destroy ( & xdr ) ;
 conn = client -> conn ;
 virMutexUnlock ( & client -> lock ) ;
 rv = ( data -> fn ) ( server , client , conn , & msg -> hdr , & rerr , & args , & ret ) ;
 virMutexLock ( & server -> lock ) ;
 virMutexLock ( & client -> lock ) ;
 virMutexUnlock ( & server -> lock ) ;
 xdr_free ( data -> args_filter , ( char * ) & args ) ;
 if ( rv < 0 ) goto rpc_error ;
 msg -> hdr . type = REMOTE_REPLY ;
 msg -> hdr . status = REMOTE_OK ;
 if ( remoteEncodeClientMessageHeader ( msg ) < 0 ) {
 xdr_free ( data -> ret_filter , ( char * ) & ret ) ;
 remoteDispatchFormatError ( & rerr , "%s" , _ ( "failed to serialize reply header" ) ) ;
 goto xdr_hdr_error ;
 }
 xdrmem_create ( & xdr , msg -> buffer , msg -> bufferLength , XDR_ENCODE ) ;
 if ( xdr_setpos ( & xdr , msg -> bufferOffset ) == 0 ) {
 remoteDispatchFormatError ( & rerr , "%s" , _ ( "failed to change XDR reply offset" ) ) ;
 goto xdr_error ;
 }
 if ( ! ( ( data -> ret_filter ) ( & xdr , & ret ) ) ) {
 remoteDispatchFormatError ( & rerr , "%s" , _ ( "failed to serialize reply payload (probable message size limit)" ) ) ;
 goto xdr_error ;
 }
 msg -> bufferOffset += xdr_getpos ( & xdr ) ;
 len = msg -> bufferOffset ;
 if ( xdr_setpos ( & xdr , 0 ) == 0 ) {
 remoteDispatchFormatError ( & rerr , "%s" , _ ( "failed to change XDR reply offset" ) ) ;
 goto xdr_error ;
 }
 if ( ! xdr_u_int ( & xdr , & len ) ) {
 remoteDispatchFormatError ( & rerr , "%s" , _ ( "failed to update reply length header" ) ) ;
 goto xdr_error ;
 }
 xdr_destroy ( & xdr ) ;
 xdr_free ( data -> ret_filter , ( char * ) & ret ) ;
 msg -> bufferLength = len ;
 msg -> bufferOffset = 0 ;
 qemudClientMessageQueuePush ( & client -> tx , msg ) ;
 qemudUpdateClientEvent ( client ) ;
 return 0 ;
 xdr_error : xdr_free ( data -> ret_filter , ( char * ) & ret ) ;
 xdr_destroy ( & xdr ) ;
 xdr_hdr_error : VIR_WARN ( "Failed to serialize reply for program '%d' proc '%d' as XDR" , msg -> hdr . prog , msg -> hdr . proc ) ;
 rpc_error : rv = remoteSerializeReplyError ( client , & rerr , & msg -> hdr ) ;
 if ( rv >= 0 ) VIR_FREE ( msg ) ;
 return rv ;
 }