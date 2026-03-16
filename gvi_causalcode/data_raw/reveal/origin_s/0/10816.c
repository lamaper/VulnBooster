int qemuMonitorTextRemoveHostNetwork ( qemuMonitorPtr mon , int vlan , const char * netname ) {
 char * cmd ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "host_net_remove %d %s" , vlan , netname ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to remove host network in qemu with '%s'" ) , cmd ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }