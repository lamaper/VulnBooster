int qemuMonitorJSONAddDevice ( qemuMonitorPtr mon , const char * devicestr ) {
 int ret = - 1 ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr args ;
 cmd = qemuMonitorJSONMakeCommand ( "device_add" , NULL ) ;
 if ( ! cmd ) return - 1 ;
 args = qemuMonitorJSONKeywordStringToJSON ( devicestr , "driver" ) ;
 if ( ! args ) goto cleanup ;
 if ( virJSONValueObjectAppend ( cmd , "arguments" , args ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 args = NULL ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 cleanup : virJSONValueFree ( args ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }