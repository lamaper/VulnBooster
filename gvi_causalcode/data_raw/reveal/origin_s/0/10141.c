int qemuMonitorJSONOpenGraphics ( qemuMonitorPtr mon , const char * protocol , const char * fdname , bool skipauth ) {
 int ret ;
 virJSONValuePtr cmd , reply = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "add_client" , "s:protocol" , protocol , "s:fdname" , fdname , "b:skipauth" , skipauth , NULL ) ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }