int qemuMonitorJSONSetLink ( qemuMonitorPtr mon , const char * name , enum virDomainNetInterfaceLinkState state ) {
 int ret ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "set_link" , "s:name" , name , "b:up" , state != VIR_DOMAIN_NET_INTERFACE_LINK_STATE_DOWN , NULL ) ;
 if ( ! cmd ) return - 1 ;
 if ( ( ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ) == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }