struct qemud_client_stream * remoteCreateClientStream ( virConnectPtr conn , remote_message_header * hdr ) {
 struct qemud_client_stream * stream ;
 VIR_DEBUG ( "proc=%d serial=%d" , hdr -> proc , hdr -> serial ) ;
 if ( VIR_ALLOC ( stream ) < 0 ) return NULL ;
 stream -> procedure = hdr -> proc ;
 stream -> serial = hdr -> serial ;
 stream -> st = virStreamNew ( conn , VIR_STREAM_NONBLOCK ) ;
 if ( ! stream -> st ) {
 VIR_FREE ( stream ) ;
 return NULL ;
 }
 stream -> filter . query = remoteStreamFilter ;
 stream -> filter . opaque = stream ;
 return stream ;
 }