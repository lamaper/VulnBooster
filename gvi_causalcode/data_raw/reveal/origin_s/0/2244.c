int qemuMonitorTextSendFileHandle ( qemuMonitorPtr mon , const char * fdname , int fd ) {
 char * cmd ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "getfd %s" , fdname ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommandWithFd ( mon , cmd , fd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to pass fd to qemu with '%s'" ) , cmd ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "unknown command:" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "qemu does not support sending of file handles: %s" ) , reply ) ;
 goto cleanup ;
 }
 if ( STRNEQ ( reply , "" ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unable to send file handle '%s': %s" ) , fdname , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }