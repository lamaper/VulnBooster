int qemuMonitorJSONStartCPUs ( qemuMonitorPtr mon , virConnectPtr conn ATTRIBUTE_UNUSED ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "cont" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 int i = 0 , timeout = 3 ;
 if ( ! cmd ) return - 1 ;
 do {
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret != 0 ) break ;
 if ( ( ret = qemuMonitorJSONCheckError ( cmd , reply ) ) == 0 ) break ;
 if ( ! qemuMonitorJSONHasError ( reply , "MigrationExpected" ) ) break ;
 virJSONValueFree ( reply ) ;
 reply = NULL ;
 usleep ( 250000 ) ;
 }
 while ( ++ i <= timeout ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }