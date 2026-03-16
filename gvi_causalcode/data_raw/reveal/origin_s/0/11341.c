int qemuMonitorJSONSetVNCPassword ( qemuMonitorPtr mon , const char * password ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "change" , "s:device" , "vnc" , "s:target" , "password" , "s:arg" , password , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }