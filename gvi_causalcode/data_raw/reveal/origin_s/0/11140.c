int remoteDecodeClientMessageHeader ( struct qemud_client_message * msg ) {
 XDR xdr ;
 int ret = - 1 ;
 msg -> bufferOffset = REMOTE_MESSAGE_HEADER_XDR_LEN ;
 xdrmem_create ( & xdr , msg -> buffer + msg -> bufferOffset , msg -> bufferLength - msg -> bufferOffset , XDR_DECODE ) ;
 if ( ! xdr_remote_message_header ( & xdr , & msg -> hdr ) ) goto cleanup ;
 msg -> bufferOffset += xdr_getpos ( & xdr ) ;
 ret = 0 ;
 cleanup : xdr_destroy ( & xdr ) ;
 return ret ;
 }