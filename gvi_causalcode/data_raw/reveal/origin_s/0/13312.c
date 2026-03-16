int qemuMonitorTextGetBalloonInfo ( qemuMonitorPtr mon , unsigned long * currmem ) {
 char * reply = NULL ;
 int ret = - 1 ;
 char * offset ;
 if ( qemuMonitorHMPCommand ( mon , "info balloon" , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "could not query memory balloon allocation" ) ) ;
 return - 1 ;
 }
 if ( ( offset = strstr ( reply , BALLOON_PREFIX ) ) != NULL ) {
 offset += strlen ( BALLOON_PREFIX ) ;
 struct _virDomainMemoryStat stats [ 1 ] ;
 if ( qemuMonitorParseBalloonInfo ( offset , stats , 1 ) == 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unexpected balloon information '%s'" ) , reply ) ;
 goto cleanup ;
 }
 if ( stats [ 0 ] . tag != VIR_DOMAIN_MEMORY_STAT_ACTUAL_BALLOON ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unexpected balloon information '%s'" ) , reply ) ;
 goto cleanup ;
 }
 * currmem = stats [ 0 ] . val ;
 ret = 1 ;
 }
 else {
 ret = 0 ;
 }
 cleanup : VIR_FREE ( reply ) ;
 return ret ;
 }