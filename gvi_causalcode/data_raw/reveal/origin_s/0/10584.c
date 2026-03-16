int qemuMonitorTextInjectNMI ( qemuMonitorPtr mon ) {
 const char * cmd = "inject-nmi" ;
 char * reply = NULL ;
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) goto fail ;
 if ( strstr ( reply , "unknown command" ) != NULL ) {
 VIR_FREE ( reply ) ;
 cmd = "nmi 0" ;
 reply = NULL ;
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) goto fail ;
 }
 VIR_FREE ( reply ) ;
 return 0 ;
 fail : qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to inject NMI using command '%s'" ) , cmd ) ;
 return - 1 ;
 }