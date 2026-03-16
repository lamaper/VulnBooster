int qemuMonitorJSONAddDrive ( qemuMonitorPtr mon , const char * drivestr ) {
 int ret ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "drive_add" , "s:pci_addr" , "dummy" , "s:opts" , drivestr , NULL ) ;
 if ( ! cmd ) return - 1 ;
 if ( ( ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) < 0 ) ) goto cleanup ;
 if ( qemuMonitorJSONHasError ( reply , "CommandNotFound" ) && qemuMonitorCheckHMP ( mon , "drive_add" ) ) {
 VIR_DEBUG ( "drive_add command not found, trying HMP" ) ;
 ret = qemuMonitorTextAddDrive ( mon , drivestr ) ;
 goto cleanup ;
 }
 ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }