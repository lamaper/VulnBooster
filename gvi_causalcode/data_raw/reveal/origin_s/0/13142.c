int qemuMonitorTextExpirePassword ( qemuMonitorPtr mon , const char * protocol , const char * expire_time ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "expire_password %s %s" , protocol , expire_time ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "expiring password failed" ) ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "unknown command:" ) ) {
 ret = - 2 ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( reply ) ;
 VIR_FREE ( cmd ) ;
 return ret ;
 }