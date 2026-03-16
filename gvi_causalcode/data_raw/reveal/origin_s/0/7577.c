int qemuMonitorJSONRemoveHostNetwork ( qemuMonitorPtr mon , int vlan , const char * netname ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "host_net_remove" , "i:vlan" , vlan , "s:device" , netname , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }