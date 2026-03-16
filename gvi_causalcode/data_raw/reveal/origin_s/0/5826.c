int remoteEncodeClientMessageHeader ( struct qemud_client_message * msg ) {
 XDR xdr ;
 int ret = - 1 ;
 unsigned int len = 0 ;
 msg -> bufferLength = sizeof ( msg -> buffer ) ;
 msg -> bufferOffset = 0 ;
 xdrmem_create ( & xdr , msg -> buffer , msg -> bufferLength , XDR_ENCODE ) ;
 if ( ! xdr_u_int ( & xdr , & len ) ) {
 goto cleanup ;
 }
 if ( ! xdr_remote_message_header ( & xdr , & msg -> hdr ) ) goto cleanup ;
 len = xdr_getpos ( & xdr ) ;
 xdr_setpos ( & xdr , 0 ) ;
 if ( ! xdr_u_int ( & xdr , & len ) ) {
 goto cleanup ;
 }
 msg -> bufferOffset += len ;
 ret = 0 ;
 cleanup : xdr_destroy ( & xdr ) ;
 return ret ;
 }