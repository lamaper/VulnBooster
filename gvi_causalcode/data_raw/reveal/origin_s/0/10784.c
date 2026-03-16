int qemuAgentSuspend ( qemuAgentPtr mon , unsigned int target ) {
 int ret = - 1 ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuAgentMakeCommand ( qemuAgentSuspendModeTypeToString ( target ) , NULL ) ;
 if ( ! cmd ) return - 1 ;
 mon -> await_event = QEMU_AGENT_EVENT_SUSPEND ;
 ret = qemuAgentCommand ( mon , cmd , & reply , false , VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }