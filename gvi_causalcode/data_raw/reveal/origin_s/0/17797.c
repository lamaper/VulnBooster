int qemuMonitorTextSetLink ( qemuMonitorPtr mon , const char * name , enum virDomainNetInterfaceLinkState state ) {
 char * info = NULL ;
 char * cmd = NULL ;
 const char * st_str = NULL ;
 if ( state == VIR_DOMAIN_NET_INTERFACE_LINK_STATE_DOWN ) st_str = "off" ;
 else st_str = "on" ;
 if ( virAsprintf ( & cmd , "set_link %s %s" , name , st_str ) < 0 ) {
 virReportOOMError ( ) ;
 goto error ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "set_link operation failed" ) ) ;
 goto error ;
 }
 if ( strstr ( info , "\nunknown " ) ) {
 qemuReportError ( VIR_ERR_NO_SUPPORT , "%s" , _ ( "\'set_link\' not supported by this qemu" ) ) ;
 goto error ;
 }
 if ( strstr ( info , "\nDevice " ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "device name rejected" ) ) ;
 goto error ;
 }
 VIR_FREE ( info ) ;
 VIR_FREE ( cmd ) ;
 return 0 ;
 error : VIR_FREE ( info ) ;
 VIR_FREE ( cmd ) ;
 return - 1 ;
 }