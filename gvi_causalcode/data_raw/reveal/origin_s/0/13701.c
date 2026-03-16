int qemuMonitorJSONGraphicsRelocate ( qemuMonitorPtr mon , int type , const char * hostname , int port , int tlsPort , const char * tlsSubject ) {
 int ret = - 1 ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "client_migrate_info" , "s:protocol" , ( type == VIR_DOMAIN_GRAPHICS_TYPE_SPICE ? "spice" : "vnc" ) , "s:hostname" , hostname , "i:port" , port , "i:tls-port" , tlsPort , ( tlsSubject ? "s:cert-subject" : NULL ) , ( tlsSubject ? tlsSubject : NULL ) , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }