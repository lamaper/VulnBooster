int qemuMonitorTextGetBlockIoThrottle ( qemuMonitorPtr mon , const char * device , virDomainBlockIoTuneInfoPtr reply ) {
 char * result = NULL ;
 int ret = 0 ;
 const char * cmd_name = "info block" ;
 if ( qemuMonitorHMPCommand ( mon , cmd_name , & result ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot run monitor command" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 if ( qemuMonitorTextCommandNotFound ( cmd_name , result ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "Command '%s' is not found" ) , cmd_name ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 ret = qemuMonitorTextParseBlockIoThrottle ( result , device , reply ) ;
 cleanup : VIR_FREE ( result ) ;
 return ret ;
 }