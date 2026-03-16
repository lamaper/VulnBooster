int qemuMonitorTextSetBlockIoThrottle ( qemuMonitorPtr mon , const char * device , virDomainBlockIoTuneInfoPtr info ) {
 char * cmd = NULL ;
 char * result = NULL ;
 int ret = 0 ;
 const char * cmd_name = NULL ;
 cmd_name = "block_set_io_throttle" ;
 ret = virAsprintf ( & cmd , "%s %s %llu %llu %llu %llu %llu %llu" , cmd_name , device , info -> total_bytes_sec , info -> read_bytes_sec , info -> write_bytes_sec , info -> total_iops_sec , info -> read_iops_sec , info -> write_iops_sec ) ;
 if ( ret < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & result ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot run monitor command" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 if ( qemuMonitorTextCommandNotFound ( cmd_name , result ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "Command '%s' is not found" ) , cmd_name ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( result ) ;
 return ret ;
 }