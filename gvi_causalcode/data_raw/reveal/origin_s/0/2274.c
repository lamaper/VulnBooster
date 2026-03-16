int qemuMonitorTextMigrateCancel ( qemuMonitorPtr mon ) {
 char * info = NULL ;
 if ( qemuMonitorHMPCommand ( mon , "migrate_cancel" , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot run monitor command to cancel migration" ) ) ;
 return - 1 ;
 }
 VIR_FREE ( info ) ;
 return 0 ;
 }