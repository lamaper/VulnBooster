int qemuMonitorTextScreendump ( qemuMonitorPtr mon , const char * file ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "screendump %s" , file ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "taking screenshot failed" ) ) ;
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