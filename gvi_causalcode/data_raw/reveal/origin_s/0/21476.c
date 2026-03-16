int qemuAgentSetTime ( qemuAgentPtr mon , long long seconds , unsigned int nseconds , bool rtcSync ) {
 int ret = - 1 ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 if ( rtcSync ) {
 cmd = qemuAgentMakeCommand ( "guest-set-time" , NULL ) ;
 }
 else {
 long long json_time ;
 if ( seconds > LLONG_MAX / 1000000000LL ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "Time '%lld' is too big for guest agent" ) , seconds ) ;
 return ret ;
 }
 json_time = seconds * 1000000000LL ;
 json_time += nseconds ;
 cmd = qemuAgentMakeCommand ( "guest-set-time" , "I:time" , json_time , NULL ) ;
 }
 if ( ! cmd ) return ret ;
 if ( qemuAgentCommand ( mon , cmd , & reply , true , VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) < 0 ) goto cleanup ;
 ret = 0 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }