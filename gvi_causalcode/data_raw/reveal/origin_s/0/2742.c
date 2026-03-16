int qemuMonitorTextCloseFileHandle ( qemuMonitorPtr mon , const char * fdname ) {
 char * cmd ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "closefd %s" , fdname ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to close fd in qemu with '%s'" ) , cmd ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "unknown command:" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "qemu does not support closing of file handles: %s" ) , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }