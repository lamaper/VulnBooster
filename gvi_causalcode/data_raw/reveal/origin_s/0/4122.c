int qemuMonitorJSONBlockResize ( qemuMonitorPtr mon , const char * device , unsigned long long size ) {
 int ret ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "block_resize" , "s:device" , device , "U:size" , size * 1024 , NULL ) ;
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