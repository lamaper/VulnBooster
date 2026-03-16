int qemuMonitorJSONDeleteSnapshot ( qemuMonitorPtr mon , const char * name ) {
 int ret ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "delvm" , "s:name" , name , NULL ) ;
 if ( ! cmd ) return - 1 ;
 if ( ( ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ) < 0 ) goto cleanup ;
 if ( qemuMonitorJSONHasError ( reply , "CommandNotFound" ) && qemuMonitorCheckHMP ( mon , "delvm" ) ) {
 VIR_DEBUG ( "delvm command not found, trying HMP" ) ;
 ret = qemuMonitorTextDeleteSnapshot ( mon , name ) ;
 goto cleanup ;
 }
 ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }