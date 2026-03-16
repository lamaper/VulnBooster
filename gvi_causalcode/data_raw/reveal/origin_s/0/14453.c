int qemuMonitorJSONInjectNMI ( qemuMonitorPtr mon ) {
 int ret ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "inject-nmi" , NULL ) ;
 if ( ! cmd ) return - 1 ;
 if ( ( ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ) < 0 ) goto cleanup ;
 if ( qemuMonitorJSONHasError ( reply , "CommandNotFound" ) && qemuMonitorCheckHMP ( mon , "inject-nmi" ) ) {
 VIR_DEBUG ( "inject-nmi command not found, trying HMP" ) ;
 ret = qemuMonitorTextInjectNMI ( mon ) ;
 }
 else {
 ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 }
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }