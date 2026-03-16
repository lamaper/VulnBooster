int qemuMonitorJSONAddHostNetwork ( qemuMonitorPtr mon , const char * netstr ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "host_net_add" , "s:device" , netstr , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }