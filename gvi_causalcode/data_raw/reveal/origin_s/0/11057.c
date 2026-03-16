int qemuMonitorTextSystemPowerdown ( qemuMonitorPtr mon ) {
 char * info ;
 if ( qemuMonitorHMPCommand ( mon , "system_powerdown" , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "system shutdown operation failed" ) ) ;
 return - 1 ;
 }
 VIR_FREE ( info ) ;
 return 0 ;
 }