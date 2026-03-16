int qemuMonitorJSONSetMigrationDowntime ( qemuMonitorPtr mon , unsigned long long downtime ) {
 int ret ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "migrate_set_downtime" , "d:value" , downtime / 1000.0 , NULL ) ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }