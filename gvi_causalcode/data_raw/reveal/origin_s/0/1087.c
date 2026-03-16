int qemuMonitorTextCreateSnapshot ( qemuMonitorPtr mon , const char * name ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 char * safename ;
 if ( ! ( safename = qemuMonitorEscapeArg ( name ) ) || virAsprintf ( & cmd , "savevm \"%s\"" , safename ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to take snapshot using command '%s'" ) , cmd ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "Error while creating snapshot" ) != NULL ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "Failed to take snapshot: %s" ) , reply ) ;
 goto cleanup ;
 }
 else if ( strstr ( reply , "No block device can accept snapshots" ) != NULL ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , "%s" , _ ( "this domain does not have a device to take snapshots" ) ) ;
 goto cleanup ;
 }
 else if ( strstr ( reply , "Could not open VM state file" ) != NULL ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , reply ) ;
 goto cleanup ;
 }
 else if ( strstr ( reply , "Error" ) != NULL && strstr ( reply , "while writing VM" ) != NULL ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( safename ) ;
 VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }