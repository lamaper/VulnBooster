static int qemuAgentCommand ( qemuAgentPtr mon , virJSONValuePtr cmd , virJSONValuePtr * reply , bool needReply , int seconds ) {
 int ret = - 1 ;
 qemuAgentMessage msg ;
 char * cmdstr = NULL ;
 int await_event = mon -> await_event ;
 * reply = NULL ;
 if ( ! mon -> running ) {
 virReportError ( VIR_ERR_AGENT_UNRESPONSIVE , "%s" , _ ( "Guest agent disappeared while executing command" ) ) ;
 return - 1 ;
 }
 if ( qemuAgentGuestSync ( mon ) < 0 ) return - 1 ;
 memset ( & msg , 0 , sizeof ( msg ) ) ;
 if ( ! ( cmdstr = virJSONValueToString ( cmd , false ) ) ) goto cleanup ;
 if ( virAsprintf ( & msg . txBuffer , "%s" LINE_ENDING , cmdstr ) < 0 ) goto cleanup ;
 msg . txLength = strlen ( msg . txBuffer ) ;
 VIR_DEBUG ( "Send command '%s' for write, seconds = %d" , cmdstr , seconds ) ;
 ret = qemuAgentSend ( mon , & msg , seconds ) ;
 VIR_DEBUG ( "Receive command reply ret=%d rxObject=%p" , ret , msg . rxObject ) ;
 if ( ret == 0 ) {
 if ( ! msg . rxObject ) {
 if ( await_event && ! needReply ) {
 VIR_DEBUG ( "Woken up by event %d" , await_event ) ;
 }
 else {
 if ( mon -> running ) virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Missing monitor reply object" ) ) ;
 else virReportError ( VIR_ERR_AGENT_UNRESPONSIVE , "%s" , _ ( "Guest agent disappeared while executing command" ) ) ;
 ret = - 1 ;
 }
 }
 else {
 * reply = msg . rxObject ;
 ret = qemuAgentCheckError ( cmd , * reply ) ;
 }
 }
 cleanup : VIR_FREE ( cmdstr ) ;
 VIR_FREE ( msg . txBuffer ) ;
 return ret ;
 }