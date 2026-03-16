static int qemuAgentGuestSync ( qemuAgentPtr mon ) {
 int ret = - 1 ;
 int send_ret ;
 unsigned long long id ;
 qemuAgentMessage sync_msg ;
 memset ( & sync_msg , 0 , sizeof ( sync_msg ) ) ;
 sync_msg . first = true ;
 retry : if ( virTimeMillisNow ( & id ) < 0 ) return - 1 ;
 if ( virAsprintf ( & sync_msg . txBuffer , "{
\"execute\":\"guest-sync\", " "\"arguments\":{
\"id\":%llu}
}
\n" , id ) < 0 ) return - 1 ;
 sync_msg . txLength = strlen ( sync_msg . txBuffer ) ;
 sync_msg . sync = true ;
 sync_msg . id = id ;
 VIR_DEBUG ( "Sending guest-sync command with ID: %llu" , id ) ;
 send_ret = qemuAgentSend ( mon , & sync_msg , VIR_DOMAIN_QEMU_AGENT_COMMAND_DEFAULT ) ;
 VIR_DEBUG ( "qemuAgentSend returned: %d" , send_ret ) ;
 if ( send_ret < 0 ) goto cleanup ;
 if ( ! sync_msg . rxObject ) {
 if ( sync_msg . first ) {
 VIR_FREE ( sync_msg . txBuffer ) ;
 memset ( & sync_msg , 0 , sizeof ( sync_msg ) ) ;
 goto retry ;
 }
 else {
 if ( mon -> running ) virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Missing monitor reply object" ) ) ;
 else virReportError ( VIR_ERR_AGENT_UNRESPONSIVE , "%s" , _ ( "Guest agent disappeared while executing command" ) ) ;
 goto cleanup ;
 }
 }
 ret = 0 ;
 cleanup : virJSONValueFree ( sync_msg . rxObject ) ;
 VIR_FREE ( sync_msg . txBuffer ) ;
 return ret ;
 }