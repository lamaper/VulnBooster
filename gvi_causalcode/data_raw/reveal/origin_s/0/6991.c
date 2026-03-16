int qemuAgentFSFreeze ( qemuAgentPtr mon , const char * * mountpoints , unsigned int nmountpoints ) {
 int ret = - 1 ;
 virJSONValuePtr cmd , arg = NULL ;
 virJSONValuePtr reply = NULL ;
 if ( mountpoints && nmountpoints ) {
 arg = qemuAgentMakeStringsArray ( mountpoints , nmountpoints ) ;
 if ( ! arg ) return - 1 ;
 cmd = qemuAgentMakeCommand ( "guest-fsfreeze-freeze-list" , "a:mountpoints" , arg , NULL ) ;
 }
 else {
 cmd = qemuAgentMakeCommand ( "guest-fsfreeze-freeze" , NULL ) ;
 }
 if ( ! cmd ) goto cleanup ;
 arg = NULL ;
 if ( qemuAgentCommand ( mon , cmd , & reply , true , VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) < 0 ) goto cleanup ;
 if ( virJSONValueObjectGetNumberInt ( reply , "return" , & ret ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "malformed return value" ) ) ;
 }
 cleanup : virJSONValueFree ( arg ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }