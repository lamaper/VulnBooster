int qemuMonitorJSONLoadSnapshot ( qemuMonitorPtr mon , const char * name ) {
 int ret ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "loadvm" , "s:name" , name , NULL ) ;
 if ( ! cmd ) return - 1 ;
 if ( ( ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ) < 0 ) goto cleanup ;
 if ( qemuMonitorJSONHasError ( reply , "CommandNotFound" ) && qemuMonitorCheckHMP ( mon , "loadvm" ) ) {
 VIR_DEBUG ( "loadvm command not found, trying HMP" ) ;
 ret = qemuMonitorTextLoadSnapshot ( mon , name ) ;
 goto cleanup ;
 }
 ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }