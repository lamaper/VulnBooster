static int qemuMonitorJSONCommandWithFd ( qemuMonitorPtr mon , virJSONValuePtr cmd , int scm_fd , virJSONValuePtr * reply ) {
 int ret = - 1 ;
 qemuMonitorMessage msg ;
 char * cmdstr = NULL ;
 char * id = NULL ;
 virJSONValuePtr exe ;
 * reply = NULL ;
 memset ( & msg , 0 , sizeof msg ) ;
 exe = virJSONValueObjectGet ( cmd , "execute" ) ;
 if ( exe ) {
 if ( ! ( id = qemuMonitorNextCommandID ( mon ) ) ) goto cleanup ;
 if ( virJSONValueObjectAppendString ( cmd , "id" , id ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Unable to append command 'id' string" ) ) ;
 goto cleanup ;
 }
 }
 if ( ! ( cmdstr = virJSONValueToString ( cmd ) ) ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( virAsprintf ( & msg . txBuffer , "%s\r\n" , cmdstr ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 msg . txLength = strlen ( msg . txBuffer ) ;
 msg . txFD = scm_fd ;
 VIR_DEBUG ( "Send command '%s' for write with FD %d" , cmdstr , scm_fd ) ;
 ret = qemuMonitorSend ( mon , & msg ) ;
 VIR_DEBUG ( "Receive command reply ret=%d rxObject=%p" , ret , msg . rxObject ) ;
 if ( ret == 0 ) {
 if ( ! msg . rxObject ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Missing monitor reply object" ) ) ;
 ret = - 1 ;
 }
 else {
 * reply = msg . rxObject ;
 }
 }
 cleanup : VIR_FREE ( id ) ;
 VIR_FREE ( cmdstr ) ;
 VIR_FREE ( msg . txBuffer ) ;
 return ret ;
 }