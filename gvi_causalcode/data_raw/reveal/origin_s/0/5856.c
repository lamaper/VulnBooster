static int qemuMonitorTextCommandWithHandler ( qemuMonitorPtr mon , const char * cmd , qemuMonitorPasswordHandler passwordHandler , void * passwordOpaque , int scm_fd , char * * reply ) {
 int ret ;
 qemuMonitorMessage msg ;
 * reply = NULL ;
 memset ( & msg , 0 , sizeof msg ) ;
 if ( virAsprintf ( & msg . txBuffer , "%s\r" , cmd ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 msg . txLength = strlen ( msg . txBuffer ) ;
 msg . txFD = scm_fd ;
 msg . passwordHandler = passwordHandler ;
 msg . passwordOpaque = passwordOpaque ;
 VIR_DEBUG ( "Send command '%s' for write with FD %d" , cmd , scm_fd ) ;
 ret = qemuMonitorSend ( mon , & msg ) ;
 VIR_DEBUG ( "Receive command reply ret=%d rxLength=%d rxBuffer='%s'" , ret , msg . rxLength , msg . rxBuffer ) ;
 memset ( msg . txBuffer , 0 , msg . txLength ) ;
 VIR_FREE ( msg . txBuffer ) ;
 if ( ret >= 0 ) {
 if ( msg . rxBuffer ) {
 * reply = msg . rxBuffer ;
 }
 else {
 * reply = strdup ( "" ) ;
 if ( ! * reply ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 }
 }
 return ret ;
 }