int qemuMonitorTextAddHostNetwork ( qemuMonitorPtr mon , const char * netstr ) {
 char * cmd ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "host_net_add %s" , netstr ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to add host net with '%s'" ) , cmd ) ;
 goto cleanup ;
 }
 if ( STRNEQ ( reply , "" ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unable to add host net: %s" ) , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }