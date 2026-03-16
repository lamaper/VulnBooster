int qemuAgentShutdown ( qemuAgentPtr mon , qemuAgentShutdownMode mode ) {
 int ret = - 1 ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuAgentMakeCommand ( "guest-shutdown" , "s:mode" , qemuAgentShutdownModeTypeToString ( mode ) , NULL ) ;
 if ( ! cmd ) return - 1 ;
 if ( mode == QEMU_AGENT_SHUTDOWN_REBOOT ) mon -> await_event = QEMU_AGENT_EVENT_RESET ;
 else mon -> await_event = QEMU_AGENT_EVENT_SHUTDOWN ;
 ret = qemuAgentCommand ( mon , cmd , & reply , false , VIR_DOMAIN_QEMU_AGENT_COMMAND_SHUTDOWN ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }