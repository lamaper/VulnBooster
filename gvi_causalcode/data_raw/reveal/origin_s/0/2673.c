int qemuMonitorJSONSetPassword ( qemuMonitorPtr mon , const char * protocol , const char * password , const char * action_if_connected ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "set_password" , "s:protocol" , protocol , "s:password" , password , "s:connected" , action_if_connected , NULL ) ;
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