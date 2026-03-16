int qemuAgentGetTime ( qemuAgentPtr mon , long long * seconds , unsigned int * nseconds ) {
 int ret = - 1 ;
 unsigned long long json_time ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuAgentMakeCommand ( "guest-get-time" , NULL ) ;
 if ( ! cmd ) return ret ;
 if ( qemuAgentCommand ( mon , cmd , & reply , true , VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) < 0 ) goto cleanup ;
 if ( virJSONValueObjectGetNumberUlong ( reply , "return" , & json_time ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "malformed return value" ) ) ;
 goto cleanup ;
 }
 * seconds = json_time / 1000000000LL ;
 * nseconds = json_time % 1000000000LL ;
 ret = 0 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }