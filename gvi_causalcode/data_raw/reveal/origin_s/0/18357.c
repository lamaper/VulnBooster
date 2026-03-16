int qemuMonitorJSONGetMigrationStatus ( qemuMonitorPtr mon , int * status , unsigned long long * transferred , unsigned long long * remaining , unsigned long long * total ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-migrate" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 * status = 0 ;
 * transferred = * remaining = * total = 0 ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret == 0 && qemuMonitorJSONGetMigrationStatusReply ( reply , status , transferred , remaining , total ) < 0 ) ret = - 1 ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }