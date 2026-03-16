int qemuMonitorJSONCloseFileHandle ( qemuMonitorPtr mon , const char * fdname ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "closefd" , "s:fdname" , fdname , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }