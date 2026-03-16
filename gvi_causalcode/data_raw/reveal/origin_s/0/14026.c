int qemuMonitorJSONDriveDel ( qemuMonitorPtr mon , const char * drivestr ) {
 int ret ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 VIR_DEBUG ( "JSONDriveDel drivestr=%s" , drivestr ) ;
 cmd = qemuMonitorJSONMakeCommand ( "drive_del" , "s:id" , drivestr , NULL ) ;
 if ( ! cmd ) return - 1 ;
 if ( ( ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ) < 0 ) goto cleanup ;
 if ( qemuMonitorJSONHasError ( reply , "CommandNotFound" ) ) {
 if ( qemuMonitorCheckHMP ( mon , "drive_del" ) ) {
 VIR_DEBUG ( "drive_del command not found, trying HMP" ) ;
 ret = qemuMonitorTextDriveDel ( mon , drivestr ) ;
 }
 else {
 VIR_ERROR ( _ ( "deleting disk is not supported. " "This may leak data if disk is reassigned" ) ) ;
 ret = 1 ;
 }
 }
 else if ( qemuMonitorJSONHasError ( reply , "DeviceNotFound" ) ) {
 ret = 0 ;
 }
 else {
 ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 }
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }