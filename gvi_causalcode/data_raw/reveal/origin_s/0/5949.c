int qemuAgentFSThaw ( qemuAgentPtr mon ) {
 int ret = - 1 ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuAgentMakeCommand ( "guest-fsfreeze-thaw" , NULL ) ;
 if ( ! cmd ) return - 1 ;
 if ( qemuAgentCommand ( mon , cmd , & reply , true , VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) < 0 ) goto cleanup ;
 if ( virJSONValueObjectGetNumberInt ( reply , "return" , & ret ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "malformed return value" ) ) ;
 }
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }