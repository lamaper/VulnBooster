int qemuMonitorJSONChangeMedia ( qemuMonitorPtr mon , const char * dev_name , const char * newmedia , const char * format ) {
 int ret ;
 virJSONValuePtr cmd ;
 if ( format ) cmd = qemuMonitorJSONMakeCommand ( "change" , "s:device" , dev_name , "s:target" , newmedia , "s:arg" , format , NULL ) ;
 else cmd = qemuMonitorJSONMakeCommand ( "change" , "s:device" , dev_name , "s:target" , newmedia , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }