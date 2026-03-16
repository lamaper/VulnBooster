static int qemuAgentSend ( qemuAgentPtr mon , qemuAgentMessagePtr msg , int seconds ) {
 int ret = - 1 ;
 unsigned long long then = 0 ;
 if ( mon -> lastError . code != VIR_ERR_OK ) {
 VIR_DEBUG ( "Attempt to send command while error is set %s" , NULLSTR ( mon -> lastError . message ) ) ;
 virSetError ( & mon -> lastError ) ;
 return - 1 ;
 }
 if ( seconds > VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) {
 unsigned long long now ;
 if ( virTimeMillisNow ( & now ) < 0 ) return - 1 ;
 if ( seconds == VIR_DOMAIN_QEMU_AGENT_COMMAND_DEFAULT ) seconds = QEMU_AGENT_WAIT_TIME ;
 then = now + seconds * 1000ull ;
 }
 mon -> msg = msg ;
 qemuAgentUpdateWatch ( mon ) ;
 while ( ! mon -> msg -> finished ) {
 if ( ( then && virCondWaitUntil ( & mon -> notify , & mon -> parent . lock , then ) < 0 ) || ( ! then && virCondWait ( & mon -> notify , & mon -> parent . lock ) < 0 ) ) {
 if ( errno == ETIMEDOUT ) {
 virReportError ( VIR_ERR_AGENT_UNRESPONSIVE , "%s" , _ ( "Guest agent not available for now" ) ) ;
 ret = - 2 ;
 }
 else {
 virReportSystemError ( errno , "%s" , _ ( "Unable to wait on agent monitor " "condition" ) ) ;
 }
 goto cleanup ;
 }
 }
 if ( mon -> lastError . code != VIR_ERR_OK ) {
 VIR_DEBUG ( "Send command resulted in error %s" , NULLSTR ( mon -> lastError . message ) ) ;
 virSetError ( & mon -> lastError ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : mon -> msg = NULL ;
 qemuAgentUpdateWatch ( mon ) ;
 return ret ;
 }