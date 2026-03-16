int qemuMonitorJSONGetCPUInfo ( qemuMonitorPtr mon , int * * pids ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-cpus" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 * pids = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONExtractCPUInfo ( reply , pids ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }