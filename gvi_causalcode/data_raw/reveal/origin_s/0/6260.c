int qemuMonitorJSONSendFileHandle ( qemuMonitorPtr mon , const char * fdname , int fd ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "getfd" , "s:fdname" , fdname , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommandWithFd ( mon , cmd , fd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }