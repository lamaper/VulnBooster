int qemuMonitorTextBlockJob ( qemuMonitorPtr mon , const char * device , unsigned long bandwidth , virDomainBlockJobInfoPtr info , int mode ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret ;
 const char * cmd_name = NULL ;
 if ( mode == BLOCK_JOB_ABORT ) {
 cmd_name = "block_job_cancel" ;
 ret = virAsprintf ( & cmd , "%s %s" , cmd_name , device ) ;
 }
 else if ( mode == BLOCK_JOB_INFO ) {
 cmd_name = "info block-jobs" ;
 ret = virAsprintf ( & cmd , "%s" , cmd_name ) ;
 }
 else if ( mode == BLOCK_JOB_SPEED ) {
 cmd_name = "block_job_set_speed" ;
 ret = virAsprintf ( & cmd , "%s %s %luM" , cmd_name , device , bandwidth ) ;
 }
 else if ( mode == BLOCK_JOB_PULL ) {
 cmd_name = "block_stream" ;
 ret = virAsprintf ( & cmd , "%s %s" , cmd_name , device ) ;
 }
 else {
 return - 1 ;
 }
 if ( ret < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot run monitor command" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 if ( qemuMonitorTextCommandNotFound ( cmd_name , reply ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "Command '%s' is not found" ) , cmd_name ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 ret = qemuMonitorTextParseBlockJob ( reply , device , info ) ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }