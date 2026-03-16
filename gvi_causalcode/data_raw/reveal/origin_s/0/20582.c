int qemuAgentFSTrim ( qemuAgentPtr mon , unsigned long long minimum ) {
 int ret = - 1 ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuAgentMakeCommand ( "guest-fstrim" , "U:minimum" , minimum , NULL ) ;
 if ( ! cmd ) return ret ;
 ret = qemuAgentCommand ( mon , cmd , & reply , false , VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }