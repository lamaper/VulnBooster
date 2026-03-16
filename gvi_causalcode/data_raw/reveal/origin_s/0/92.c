int qemuMonitorJSONScreendump ( qemuMonitorPtr mon , const char * file ) {
 int ret ;
 virJSONValuePtr cmd , reply = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "screendump" , "s:filename" , file , NULL ) ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }