static void qemuAgentIO ( int watch , int fd , int events , void * opaque ) {
 qemuAgentPtr mon = opaque ;
 bool error = false ;
 bool eof = false ;
 virObjectRef ( mon ) ;
 virObjectLock ( mon ) ;


 if ( events & ( VIR_EVENT_HANDLE_HANGUP | VIR_EVENT_HANDLE_ERROR ) ) eof = true ;
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "event from unexpected fd %d!=%d / watch %d!=%d" ) , mon -> fd , fd , mon -> watch , watch ) ;
 error = true ;
 }
 else if ( mon -> lastError . code != VIR_ERR_OK ) {
 if ( events & ( VIR_EVENT_HANDLE_HANGUP | VIR_EVENT_HANDLE_ERROR ) ) eof = true ;
 error = true ;
 }
 else {
 if ( events & VIR_EVENT_HANDLE_WRITABLE ) {
 if ( mon -> connectPending ) {
 if ( qemuAgentIOConnect ( mon ) < 0 ) error = true ;
 }
 else {
 if ( qemuAgentIOWrite ( mon ) < 0 ) error = true ;
 }
 events &= ~ VIR_EVENT_HANDLE_WRITABLE ;
 }
 if ( ! error && events & VIR_EVENT_HANDLE_READABLE ) {
 int got = qemuAgentIORead ( mon ) ;
 events &= ~ VIR_EVENT_HANDLE_READABLE ;
 if ( got < 0 ) {
 error = true ;
 }
 else if ( got == 0 ) {
 eof = true ;
 }
 else {
 events = 0 ;
 if ( qemuAgentIOProcess ( mon ) < 0 ) error = true ;
 }
 }
 if ( ! error && events & VIR_EVENT_HANDLE_HANGUP ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "End of file from agent monitor" ) ) ;
 eof = true ;
 events &= ~ VIR_EVENT_HANDLE_HANGUP ;
 }
 if ( ! error && ! eof && events & VIR_EVENT_HANDLE_ERROR ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Invalid file descriptor while waiting for monitor" ) ) ;
 eof = true ;
 events &= ~ VIR_EVENT_HANDLE_ERROR ;
 }
 if ( ! error && events ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "Unhandled event %d for monitor fd %d" ) , events , mon -> fd ) ;
 error = true ;
 }
 }
 if ( error || eof ) {
 if ( mon -> lastError . code != VIR_ERR_OK ) {
 virResetLastError ( ) ;
 }
 else {
 virErrorPtr err = virGetLastError ( ) ;
 if ( ! err ) virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Error while processing monitor IO" ) ) ;
 virCopyLastError ( & mon -> lastError ) ;
 virResetLastError ( ) ;
 }
 VIR_DEBUG ( "Error on monitor %s" , NULLSTR ( mon -> lastError . message ) ) ;
 if ( mon -> msg && ! mon -> msg -> finished ) {
 mon -> msg -> finished = 1 ;
 virCondSignal ( & mon -> notify ) ;
 }
 }
 qemuAgentUpdateWatch ( mon ) ;
 if ( eof ) {
 void ( * eofNotify ) ( qemuAgentPtr , virDomainObjPtr ) = mon -> cb -> eofNotify ;
 virDomainObjPtr vm = mon -> vm ;
 virCondSignal ( & mon -> notify ) ;
 virObjectUnlock ( mon ) ;
 virObjectUnref ( mon ) ;
 VIR_DEBUG ( "Triggering EOF callback" ) ;
 ( eofNotify ) ( mon , vm ) ;
 }
 else if ( error ) {
 void ( * errorNotify ) ( qemuAgentPtr , virDomainObjPtr ) = mon -> cb -> errorNotify ;
 virDomainObjPtr vm = mon -> vm ;
 virCondSignal ( & mon -> notify ) ;
 virObjectUnlock ( mon ) ;
 virObjectUnref ( mon ) ;
 VIR_DEBUG ( "Triggering error callback" ) ;
 ( errorNotify ) ( mon , vm ) ;
 }
 else {
 virObjectUnlock ( mon ) ;
 virObjectUnref ( mon ) ;
 }
 }