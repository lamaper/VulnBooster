int qemuMonitorTextSetPassword ( qemuMonitorPtr mon , const char * protocol , const char * password , const char * action_if_connected ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "set_password %s \"%s\" %s" , protocol , password , action_if_connected ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "setting password failed" ) ) ;
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