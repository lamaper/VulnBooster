int qemuMonitorTextAddDevice ( qemuMonitorPtr mon , const char * devicestr ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 char * safedev ;
 int ret = - 1 ;
 if ( ! ( safedev = qemuMonitorEscapeArg ( devicestr ) ) ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( virAsprintf ( & cmd , "device_add %s" , safedev ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "cannot attach %s device" ) , devicestr ) ;
 goto cleanup ;
 }
 if ( STRPREFIX ( reply , "husb: using" ) ) {
 ret = 0 ;
 goto cleanup ;
 }
 if ( STRNEQ ( reply , "" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "adding %s device failed: %s" ) , devicestr , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 VIR_FREE ( safedev ) ;
 return ret ;
 }