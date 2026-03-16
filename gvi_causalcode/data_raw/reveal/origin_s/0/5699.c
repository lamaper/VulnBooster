int qemuAgentArbitraryCommand ( qemuAgentPtr mon , const char * cmd_str , char * * result , int timeout ) {
 int ret = - 1 ;
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr reply = NULL ;
 * result = NULL ;
 if ( timeout < VIR_DOMAIN_QEMU_AGENT_COMMAND_MIN ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "guest agent timeout '%d' is " "less than the minimum '%d'" ) , timeout , VIR_DOMAIN_QEMU_AGENT_COMMAND_MIN ) ;
 goto cleanup ;
 }
 if ( ! ( cmd = virJSONValueFromString ( cmd_str ) ) ) goto cleanup ;
 if ( ( ret = qemuAgentCommand ( mon , cmd , & reply , true , timeout ) ) < 0 ) goto cleanup ;
 if ( ! ( * result = virJSONValueToString ( reply , false ) ) ) ret = - 1 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }