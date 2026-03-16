int qemuMonitorJSONBlockJob ( qemuMonitorPtr mon , const char * device , unsigned long bandwidth , virDomainBlockJobInfoPtr info , int mode ) {
 int ret = - 1 ;
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr reply = NULL ;
 const char * cmd_name = NULL ;
 if ( mode == BLOCK_JOB_ABORT ) {
 cmd_name = "block_job_cancel" ;
 cmd = qemuMonitorJSONMakeCommand ( cmd_name , "s:device" , device , NULL ) ;
 }
 else if ( mode == BLOCK_JOB_INFO ) {
 cmd_name = "query-block-jobs" ;
 cmd = qemuMonitorJSONMakeCommand ( cmd_name , NULL ) ;
 }
 else if ( mode == BLOCK_JOB_SPEED ) {
 cmd_name = "block_job_set_speed" ;
 cmd = qemuMonitorJSONMakeCommand ( cmd_name , "s:device" , device , "U:value" , bandwidth * 1024ULL * 1024ULL , NULL ) ;
 }
 else if ( mode == BLOCK_JOB_PULL ) {
 cmd_name = "block_stream" ;
 cmd = qemuMonitorJSONMakeCommand ( cmd_name , "s:device" , device , NULL ) ;
 }
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 && virJSONValueObjectHasKey ( reply , "error" ) ) {
 if ( qemuMonitorJSONHasError ( reply , "DeviceNotActive" ) ) qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "No active operation on device: %s" ) , device ) ;
 else if ( qemuMonitorJSONHasError ( reply , "DeviceInUse" ) ) qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "Device %s in use" ) , device ) ;
 else if ( qemuMonitorJSONHasError ( reply , "NotSupported" ) ) qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "Operation is not supported for device: %s" ) , device ) ;
 else if ( qemuMonitorJSONHasError ( reply , "CommandNotFound" ) ) qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "Command '%s' is not found" ) , cmd_name ) ;
 else qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Unexpected error" ) ) ;
 ret = - 1 ;
 }
 if ( ret == 0 && mode == BLOCK_JOB_INFO ) ret = qemuMonitorJSONGetBlockJobInfo ( reply , device , info ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }