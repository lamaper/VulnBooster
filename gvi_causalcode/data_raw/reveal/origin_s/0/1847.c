int qemuMonitorTextArbitraryCommand ( qemuMonitorPtr mon , const char * cmd , char * * reply ) {
 char * safecmd = NULL ;
 int ret ;
 if ( ! ( safecmd = qemuMonitorEscapeArg ( cmd ) ) ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 ret = qemuMonitorHMPCommand ( mon , safecmd , reply ) ;
 if ( ret != 0 ) qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to run cmd '%s'" ) , safecmd ) ;
 VIR_FREE ( safecmd ) ;
 return ret ;
 }