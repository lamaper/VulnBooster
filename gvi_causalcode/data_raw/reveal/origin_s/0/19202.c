int qemuMonitorTextSetBalloon ( qemuMonitorPtr mon , unsigned long newmem ) {
 char * cmd ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "balloon %lu" , VIR_DIV_UP ( newmem , 1024 ) ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "could not balloon memory allocation" ) ) ;
 VIR_FREE ( cmd ) ;
 return - 1 ;
 }
 VIR_FREE ( cmd ) ;
 if ( strstr ( reply , "unknown command:" ) ) {
 ret = 0 ;
 }
 else {
 ret = 1 ;
 }
 VIR_FREE ( reply ) ;
 return ret ;
 }