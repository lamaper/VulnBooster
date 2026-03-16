int qemuMonitorJSONEjectMedia ( qemuMonitorPtr mon , const char * dev_name , bool force ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "eject" , "s:device" , dev_name , "b:force" , force ? 1 : 0 , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }