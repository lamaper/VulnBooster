static int qemuAgentIOConnect ( qemuAgentPtr mon ) {
 int optval ;
 socklen_t optlen ;
 VIR_DEBUG ( "Checking on background connection status" ) ;
 mon -> connectPending = false ;
 optlen = sizeof ( optval ) ;
 if ( getsockopt ( mon -> fd , SOL_SOCKET , SO_ERROR , & optval , & optlen ) < 0 ) {
 virReportSystemError ( errno , "%s" , _ ( "Cannot check socket connection status" ) ) ;
 return - 1 ;
 }
 if ( optval != 0 ) {
 virReportSystemError ( optval , "%s" , _ ( "Cannot connect to agent socket" ) ) ;
 return - 1 ;
 }
 VIR_DEBUG ( "Agent is now connected" ) ;
 return 0 ;
 }