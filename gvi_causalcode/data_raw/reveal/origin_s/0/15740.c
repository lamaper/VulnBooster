int qemuMonitorJSONSetBalloon ( qemuMonitorPtr mon , unsigned long newmem ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "balloon" , "U:value" , ( ( unsigned long long ) newmem ) * 1024 , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) {
 if ( qemuMonitorJSONHasError ( reply , "DeviceNotActive" ) || qemuMonitorJSONHasError ( reply , "KVMMissingCap" ) ) goto cleanup ;
 ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret == 0 ) ret = 1 ;
 }
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }