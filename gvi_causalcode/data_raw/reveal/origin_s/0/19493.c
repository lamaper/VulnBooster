int qemuMonitorTextDiskSnapshot ( qemuMonitorPtr mon , const char * device , const char * file ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 char * safename ;
 if ( ! ( safename = qemuMonitorEscapeArg ( file ) ) || virAsprintf ( & cmd , "snapshot_blkdev %s \"%s\"" , device , safename ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to take snapshot using command '%s'" ) , cmd ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "error while creating qcow2" ) != NULL || strstr ( reply , "unknown command:" ) != NULL ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "Failed to take snapshot: %s" ) , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( safename ) ;
 VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }