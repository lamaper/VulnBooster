int qemuMonitorTextDriveDel ( qemuMonitorPtr mon , const char * drivestr ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 char * safedev ;
 int ret = - 1 ;
 VIR_DEBUG ( "TextDriveDel drivestr=%s" , drivestr ) ;
 if ( ! ( safedev = qemuMonitorEscapeArg ( drivestr ) ) ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( virAsprintf ( & cmd , "drive_del %s" , safedev ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "cannot delete %s drive" ) , drivestr ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "unknown command:" ) ) {
 VIR_ERROR ( _ ( "deleting drive is not supported. " "This may leak data if disk is reassigned" ) ) ;
 ret = 1 ;
 goto cleanup ;
 }
 else if ( STRPREFIX ( reply , "Device '" ) && ( strstr ( reply , "not found" ) ) ) {
 }
 else if ( STRNEQ ( reply , "" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "deleting %s drive failed: %s" ) , drivestr , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 VIR_FREE ( safedev ) ;
 return ret ;
 }