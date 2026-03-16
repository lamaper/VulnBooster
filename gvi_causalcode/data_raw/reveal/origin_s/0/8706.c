int qemuMonitorJSONArbitraryCommand ( qemuMonitorPtr mon , const char * cmd_str , char * * reply_str , bool hmp ) {
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr reply = NULL ;
 int ret = - 1 ;
 if ( hmp ) {
 if ( ! qemuMonitorCheckHMP ( mon , NULL ) ) {
 qemuReportError ( VIR_ERR_CONFIG_UNSUPPORTED , "%s" , _ ( "HMP passthrough is not supported by qemu" " process;
 only QMP commands can be used" ) ) ;
 return - 1 ;
 }
 return qemuMonitorJSONHumanCommandWithFd ( mon , cmd_str , - 1 , reply_str ) ;
 }
 else {
 if ( ! ( cmd = virJSONValueFromString ( cmd_str ) ) ) goto cleanup ;
 if ( qemuMonitorJSONCommand ( mon , cmd , & reply ) < 0 ) goto cleanup ;
 if ( ! ( * reply_str = virJSONValueToString ( reply ) ) ) goto cleanup ;
 }
 ret = 0 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }