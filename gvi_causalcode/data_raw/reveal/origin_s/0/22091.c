static void qemuAgentNotifyCloseLocked ( qemuAgentPtr mon ) {
 if ( mon ) {
 mon -> running = false ;
 if ( mon -> msg && ! mon -> msg -> finished ) {
 mon -> msg -> finished = 1 ;
 virCondSignal ( & mon -> notify ) ;
 }
 }
 }