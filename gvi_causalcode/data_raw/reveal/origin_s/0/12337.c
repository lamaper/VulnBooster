int qemuMonitorTextGraphicsRelocate ( qemuMonitorPtr mon , int type , const char * hostname , int port , int tlsPort , const char * tlsSubject ) {
 char * cmd ;
 char * info = NULL ;
 if ( virAsprintf ( & cmd , "client_migrate_info %s %s %d %d %s" , type == VIR_DOMAIN_GRAPHICS_TYPE_SPICE ? "spice" : "vnc" , hostname , port , tlsPort , tlsSubject ? tlsSubject : "" ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & info ) < 0 ) {
 VIR_FREE ( cmd ) ;
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot run monitor command to relocate graphics client" ) ) ;
 return - 1 ;
 }
 VIR_FREE ( cmd ) ;
 VIR_FREE ( info ) ;
 return 0 ;
 }