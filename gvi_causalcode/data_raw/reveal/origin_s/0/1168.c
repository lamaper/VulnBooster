int qemuMonitorTextChangeMedia ( qemuMonitorPtr mon , const char * dev_name , const char * newmedia , const char * format ATTRIBUTE_UNUSED ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 char * safepath = NULL ;
 int ret = - 1 ;
 if ( ! ( safepath = qemuMonitorEscapeArg ( newmedia ) ) ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( virAsprintf ( & cmd , "change %s \"%s\"" , dev_name , safepath ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "could not change media on %s" ) , dev_name ) ;
 goto cleanup ;
 }
 if ( c_strcasestr ( reply , "device " ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "could not change media on %s: %s" ) , dev_name , reply ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "Could not open " ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "could not change media on %s: %s" ) , dev_name , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( reply ) ;
 VIR_FREE ( cmd ) ;
 VIR_FREE ( safepath ) ;
 return ret ;
 }