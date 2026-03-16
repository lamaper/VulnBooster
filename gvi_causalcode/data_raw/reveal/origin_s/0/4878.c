static int reassociate ( struct evport_data * epdp , struct fd_info * fdip , int fd ) {
 int sysevents = FDI_TO_SYSEVENTS ( fdip ) ;
 if ( sysevents != 0 ) {
 if ( port_associate ( epdp -> ed_port , PORT_SOURCE_FD , fd , sysevents , NULL ) == - 1 ) {
 event_warn ( "port_associate" ) ;
 return ( - 1 ) ;
 }
 }
 check_evportop ( epdp ) ;
 return ( 0 ) ;
 }