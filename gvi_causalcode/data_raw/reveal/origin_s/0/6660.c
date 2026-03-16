int qemuMonitorTextSetCPU ( qemuMonitorPtr mon , int cpu , int online ) {
 char * cmd ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "cpu_set %d %s" , cpu , online ? "online" : "offline" ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "could not change CPU online status" ) ) ;
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