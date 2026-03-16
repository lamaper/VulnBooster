int qemuMonitorJSONSetMigrationSpeed ( qemuMonitorPtr mon , unsigned long bandwidth ) {
 int ret ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "migrate_set_speed" , "U:value" , bandwidth * 1024ULL * 1024ULL , NULL ) ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }