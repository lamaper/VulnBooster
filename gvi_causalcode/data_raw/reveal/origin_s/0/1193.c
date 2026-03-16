int qemuMonitorTextAttachDrive ( qemuMonitorPtr mon , const char * drivestr , virDomainDevicePCIAddress * controllerAddr , virDomainDeviceDriveAddress * driveAddr ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 char * safe_str ;
 int tryOldSyntax = 0 ;
 safe_str = qemuMonitorEscapeArg ( drivestr ) ;
 if ( ! safe_str ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 try_command : if ( virAsprintf ( & cmd , "drive_add %s%.2x:%.2x:%.2x %s" , ( tryOldSyntax ? "" : "pci_addr=" ) , controllerAddr -> domain , controllerAddr -> bus , controllerAddr -> slot , safe_str ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to attach drive '%s'" ) , drivestr ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "unknown command:" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "drive hotplug is not supported" ) ) ;
 goto cleanup ;
 }
 if ( qemudParseDriveAddReply ( reply , driveAddr ) < 0 ) {
 if ( ! tryOldSyntax && strstr ( reply , "invalid char in expression" ) ) {
 VIR_FREE ( reply ) ;
 VIR_FREE ( cmd ) ;
 tryOldSyntax = 1 ;
 goto try_command ;
 }
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "adding %s disk failed: %s" ) , drivestr , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 VIR_FREE ( safe_str ) ;
 return ret ;
 }