int qemuMonitorJSONExpirePassword ( qemuMonitorPtr mon , const char * protocol , const char * expire_time ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "expire_password" , "s:protocol" , protocol , "s:time" , expire_time , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) {
 if ( qemuMonitorJSONHasError ( reply , "CommandNotFound" ) ) {
 ret = - 2 ;
 goto cleanup ;
 }
 ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 }
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }