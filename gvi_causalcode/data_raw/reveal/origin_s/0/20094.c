int qemuMonitorJSONGetBlockIoThrottle ( qemuMonitorPtr mon , const char * device , virDomainBlockIoTuneInfoPtr reply ) {
 int ret = - 1 ;
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr result = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "query-block" , NULL ) ;
 if ( ! cmd ) {
 return - 1 ;
 }
 ret = qemuMonitorJSONCommand ( mon , cmd , & result ) ;
 if ( ret == 0 && virJSONValueObjectHasKey ( result , "error" ) ) {
 if ( qemuMonitorJSONHasError ( result , "DeviceNotActive" ) ) qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "No active operation on device: %s" ) , device ) ;
 else if ( qemuMonitorJSONHasError ( result , "NotSupported" ) ) qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "Operation is not supported for device: %s" ) , device ) ;
 else qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Unexpected error" ) ) ;
 ret = - 1 ;
 }
 if ( ret == 0 ) ret = qemuMonitorJSONBlockIoThrottleInfo ( result , device , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( result ) ;
 return ret ;
 }