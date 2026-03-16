int qemuMonitorTextGetStatus ( qemuMonitorPtr mon , bool * running , virDomainPausedReason * reason ) {
 char * reply ;
 int ret = - 1 ;
 if ( reason ) * reason = VIR_DOMAIN_PAUSED_UNKNOWN ;
 if ( qemuMonitorHMPCommand ( mon , "info status" , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "cannot get status info" ) ) ;
 return - 1 ;
 }
 if ( strstr ( reply , "running" ) ) {
 * running = true ;
 }
 else if ( strstr ( reply , "paused" ) ) {
 char * status ;
 if ( ( status = strchr ( reply , '(' ) ) ) {
 char * end = strchr ( status , ')' ) ;
 if ( end ) * end = '\0' ;
 else status = NULL ;
 }
 if ( ! status ) VIR_DEBUG ( "info status was missing status details" ) ;
 else if ( reason ) * reason = qemuMonitorVMStatusToPausedReason ( status ) ;
 * running = false ;
 }
 else {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "unexpected reply from info status: %s" ) , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( reply ) ;
 return ret ;
 }