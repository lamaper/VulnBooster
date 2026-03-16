int qemuMonitorJSONSetBlockIoThrottle ( qemuMonitorPtr mon , const char * device , virDomainBlockIoTuneInfoPtr info ) {
 int ret = - 1 ;
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr result = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "block_set_io_throttle" , "s:device" , device , "U:bps" , info -> total_bytes_sec , "U:bps_rd" , info -> read_bytes_sec , "U:bps_wr" , info -> write_bytes_sec , "U:iops" , info -> total_iops_sec , "U:iops_rd" , info -> read_iops_sec , "U:iops_wr" , info -> write_iops_sec , NULL ) ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & result ) ;
 if ( ret == 0 && virJSONValueObjectHasKey ( result , "error" ) ) {
 if ( qemuMonitorJSONHasError ( result , "DeviceNotActive" ) ) qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "No active operation on device: %s" ) , device ) ;
 else if ( qemuMonitorJSONHasError ( result , "NotSupported" ) ) qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "Operation is not supported for device: %s" ) , device ) ;
 else qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Unexpected error" ) ) ;
 ret = - 1 ;
 }
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( result ) ;
 return ret ;
 }