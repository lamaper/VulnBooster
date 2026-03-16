int qemuMonitorTextBlockResize ( qemuMonitorPtr mon , const char * device , unsigned long long size ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "block_resize %s %llu" , device , VIR_DIV_UP ( size , 1024 ) ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "failed to resize block" ) ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "unknown command:" ) ) {
 ret = - 2 ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }