static int qemuMonitorTextParseBlockJob ( const char * text , const char * device , virDomainBlockJobInfoPtr info ) {
 const char * next = NULL ;
 int ret = 0 ;
 if ( strstr ( text , "Device '" ) && strstr ( text , "' not found" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , "%s" , _ ( "Device not found" ) ) ;
 return - 1 ;
 }
 if ( strstr ( text , "Device '" ) && strstr ( text , "' is in use" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "Device %s in use" ) , device ) ;
 return - 1 ;
 }
 if ( strstr ( text , "has not been activated" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , \ _ ( "No active operation on device: %s" ) , device ) ;
 return - 1 ;
 }
 if ( strstr ( text , "No active jobs" ) ) {
 return 0 ;
 }
 if ( strstr ( text , "Operation is not supported" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "Operation is not supported for device: %s" ) , device ) ;
 return - 1 ;
 }
 if ( STREQ ( text , "" ) ) return 0 ;
 do {
 ret = qemuMonitorTextParseBlockJobOne ( text , device , info , & next ) ;
 text = next ;
 }
 while ( text && ret == - EAGAIN ) ;
 if ( ret < 0 ) return - 1 ;
 return ret ;
 }