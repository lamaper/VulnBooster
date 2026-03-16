int qemuMonitorTextSetDrivePassphrase ( qemuMonitorPtr mon , const char * alias , const char * passphrase ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 char * safe_str ;
 safe_str = qemuMonitorEscapeArg ( passphrase ) ;
 if ( ! safe_str ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( virAsprintf ( & cmd , "block_passwd %s%s \"%s\"" , QEMU_DRIVE_HOST_PREFIX , alias , safe_str ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "failed to set disk password" ) ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "unknown command:" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "setting disk password is not supported" ) ) ;
 goto cleanup ;
 }
 else if ( strstr ( reply , "The entered password is invalid" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "the disk password is incorrect" ) ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 VIR_FREE ( safe_str ) ;
 return ret ;
 }