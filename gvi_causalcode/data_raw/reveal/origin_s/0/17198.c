int qemuMonitorTextDelDevice ( qemuMonitorPtr mon , const char * devalias ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 char * safedev ;
 int ret = - 1 ;
 if ( ! ( safedev = qemuMonitorEscapeArg ( devalias ) ) ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( virAsprintf ( & cmd , "device_del %s" , safedev ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 VIR_DEBUG ( "TextDelDevice devalias=%s" , devalias ) ;
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "cannot detach %s device" ) , devalias ) ;
 goto cleanup ;
 }
 if ( STRNEQ ( reply , "" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "detaching %s device failed: %s" ) , devalias , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 VIR_FREE ( safedev ) ;
 return ret ;
 }