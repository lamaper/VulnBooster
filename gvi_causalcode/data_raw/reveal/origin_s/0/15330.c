int qemuMonitorJSONMigrateCancel ( qemuMonitorPtr mon ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "migrate_cancel" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }