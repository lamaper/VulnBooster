int qemuMonitorTextGetMemoryStats ( qemuMonitorPtr mon , virDomainMemoryStatPtr stats , unsigned int nr_stats ) {
 char * reply = NULL ;
 int ret = 0 ;
 char * offset ;
 if ( qemuMonitorHMPCommand ( mon , "info balloon" , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "could not query memory balloon statistics" ) ) ;
 return - 1 ;
 }
 if ( ( offset = strstr ( reply , BALLOON_PREFIX ) ) != NULL ) {
 offset += strlen ( BALLOON_PREFIX ) ;
 ret = qemuMonitorParseBalloonInfo ( offset , stats , nr_stats ) ;
 }
 VIR_FREE ( reply ) ;
 return ret ;
 }