int qemuMonitorTextAddDrive ( qemuMonitorPtr mon , const char * drivestr ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 char * safe_str ;
 safe_str = qemuMonitorEscapeArg ( drivestr ) ;
 if ( ! safe_str ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( virAsprintf ( & cmd , "drive_add dummy %s" , safe_str ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to add drive '%s'" ) , drivestr ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "unknown command:" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "drive hotplug is not supported" ) ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "could not open disk image" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "open disk image file failed" ) ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 VIR_FREE ( safe_str ) ;
 return ret ;
 }