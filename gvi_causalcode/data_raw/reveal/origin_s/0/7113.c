int qemuMonitorTextDeleteSnapshot ( qemuMonitorPtr mon , const char * name ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 char * safename ;
 if ( ! ( safename = qemuMonitorEscapeArg ( name ) ) || virAsprintf ( & cmd , "delvm \"%s\"" , safename ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to delete snapshot using command '%s'" ) , cmd ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "No block device supports snapshots" ) != NULL ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , "%s" , _ ( "this domain does not have a device to delete snapshots" ) ) ;
 goto cleanup ;
 }
 else if ( strstr ( reply , "Snapshots not supported on device" ) != NULL ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , "%s" , reply ) ;
 goto cleanup ;
 }
 else if ( strstr ( reply , "Error" ) != NULL && strstr ( reply , "while deleting snapshot" ) != NULL ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( safename ) ;
 VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }