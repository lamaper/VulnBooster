static int qemuMonitorJSONSaveMemory ( qemuMonitorPtr mon , const char * cmdtype , unsigned long long offset , size_t length , const char * path ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( cmdtype , "U:val" , offset , "u:size" , length , "s:filename" , path , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }