int qemuMonitorTextEjectMedia ( qemuMonitorPtr mon , const char * dev_name , bool force ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "eject %s%s" , force ? "-f " : "" , dev_name ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "could not eject media on %s" ) , dev_name ) ;
 goto cleanup ;
 }
 if ( c_strcasestr ( reply , "device " ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "could not eject media on %s: %s" ) , dev_name , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( reply ) ;
 VIR_FREE ( cmd ) ;
 return ret ;
 }