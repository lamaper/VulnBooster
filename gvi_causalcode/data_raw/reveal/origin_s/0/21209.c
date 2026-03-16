int qemuMonitorTextOpenGraphics ( qemuMonitorPtr mon , const char * protocol , const char * fdname , bool skipauth ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "add_client %s %s %d" , protocol , fdname , skipauth ? 0 : 1 ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "adding graphics client failed" ) ) ;
 goto cleanup ;
 }
 if ( STRNEQ ( reply , "" ) ) goto cleanup ;
 ret = 0 ;
 cleanup : VIR_FREE ( reply ) ;
 VIR_FREE ( cmd ) ;
 return ret ;
 }