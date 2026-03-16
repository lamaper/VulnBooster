int qemuMonitorJSONGetPtyPaths ( qemuMonitorPtr mon , virHashTablePtr paths ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-chardev" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONExtractPtyPaths ( reply , paths ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }