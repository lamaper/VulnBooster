int qemuMonitorTextSetVNCPassword ( qemuMonitorPtr mon , const char * password ) {
 char * info = NULL ;
 if ( qemuMonitorTextCommandWithHandler ( mon , "change vnc password" , qemuMonitorSendVNCPassphrase , ( char * ) password , - 1 , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "setting VNC password failed" ) ) ;
 return - 1 ;
 }
 VIR_FREE ( info ) ;
 return 0 ;
 }