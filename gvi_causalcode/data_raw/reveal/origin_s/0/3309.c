int qemuMonitorTextStopCPUs ( qemuMonitorPtr mon ) {
 char * info ;
 if ( qemuMonitorHMPCommand ( mon , "stop" , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "cannot stop CPU execution" ) ) ;
 return - 1 ;
 }
 VIR_FREE ( info ) ;
 return 0 ;
 }