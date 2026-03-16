static void remoteStreamEvent ( virStreamPtr st , int events , void * opaque ) {
 struct qemud_client * client = opaque ;
 struct qemud_client_stream * stream ;
 virMutexLock ( & client -> lock ) ;
 stream = remoteFindClientStream ( client , st ) ;
 if ( ! stream ) {
 VIR_WARN ( "event for client=%p stream st=%p, but missing stream state" , client , st ) ;
 virStreamEventRemoveCallback ( st ) ;
 goto cleanup ;
 }
 VIR_DEBUG ( "st=%p events=%d" , st , events ) ;
 if ( events & VIR_STREAM_EVENT_WRITABLE ) {
 if ( remoteStreamHandleWrite ( client , stream ) < 0 ) {
 remoteRemoveClientStream ( client , stream ) ;
 qemudDispatchClientFailure ( client ) ;
 goto cleanup ;
 }
 }
 if ( ! stream -> recvEOF && ( events & ( VIR_STREAM_EVENT_READABLE | VIR_STREAM_EVENT_HANGUP ) ) ) {
 events = events & ~ ( VIR_STREAM_EVENT_READABLE | VIR_STREAM_EVENT_HANGUP ) ;
 if ( remoteStreamHandleRead ( client , stream ) < 0 ) {
 remoteRemoveClientStream ( client , stream ) ;
 qemudDispatchClientFailure ( client ) ;
 goto cleanup ;
 }
 }
 if ( ! stream -> closed && ( events & ( VIR_STREAM_EVENT_ERROR | VIR_STREAM_EVENT_HANGUP ) ) ) {
 int ret ;
 remote_error rerr ;
 memset ( & rerr , 0 , sizeof rerr ) ;
 stream -> closed = 1 ;
 virStreamEventRemoveCallback ( stream -> st ) ;
 virStreamAbort ( stream -> st ) ;
 if ( events & VIR_STREAM_EVENT_HANGUP ) remoteDispatchFormatError ( & rerr , "%s" , _ ( "stream had unexpected termination" ) ) ;
 else remoteDispatchFormatError ( & rerr , "%s" , _ ( "stream had I/O failure" ) ) ;
 ret = remoteSerializeStreamError ( client , & rerr , stream -> procedure , stream -> serial ) ;
 remoteRemoveClientStream ( client , stream ) ;
 if ( ret < 0 ) qemudDispatchClientFailure ( client ) ;
 goto cleanup ;
 }
 if ( stream -> closed ) {
 remoteRemoveClientStream ( client , stream ) ;
 }
 else {
 remoteStreamUpdateEvents ( stream ) ;
 }
 cleanup : virMutexUnlock ( & client -> lock ) ;
 }