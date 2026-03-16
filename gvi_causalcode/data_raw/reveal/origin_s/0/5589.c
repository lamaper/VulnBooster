int qemuMonitorTextGetAllPCIAddresses ( qemuMonitorPtr mon , qemuMonitorPCIAddress * * retaddrs ) {
 char * reply ;
 qemuMonitorPCIAddress * addrs = NULL ;
 int naddrs = 0 ;
 char * p ;
 * retaddrs = NULL ;
 if ( qemuMonitorHMPCommand ( mon , "info pci" , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "cannot query PCI addresses" ) ) ;
 return - 1 ;
 }
 p = reply ;
 while ( p ) {
 unsigned int bus , slot , func , vendor , product ;
 SKIP_TO ( p , " Bus" ) ;
 CHECK_END ( p ) ;
 SKIP_SPACE ( p ) ;
 GET_INT ( p , 10 , bus ) ;
 CHECK_END ( p ) ;
 SKIP_TO ( p , ", device" ) ;
 CHECK_END ( p ) ;
 SKIP_SPACE ( p ) ;
 GET_INT ( p , 10 , slot ) ;
 CHECK_END ( p ) ;
 SKIP_TO ( p , ", function" ) ;
 CHECK_END ( p ) ;
 SKIP_SPACE ( p ) ;
 GET_INT ( p , 10 , func ) ;
 CHECK_END ( p ) ;
 SKIP_TO ( p , "PCI device" ) ;
 CHECK_END ( p ) ;
 SKIP_SPACE ( p ) ;
 GET_INT ( p , 16 , vendor ) ;
 CHECK_END ( p ) ;
 if ( * p != ':' ) break ;
 p ++ ;
 GET_INT ( p , 16 , product ) ;
 if ( VIR_REALLOC_N ( addrs , naddrs + 1 ) < 0 ) {
 virReportOOMError ( ) ;
 goto error ;
 }
 addrs [ naddrs ] . addr . domain = 0 ;
 addrs [ naddrs ] . addr . bus = bus ;
 addrs [ naddrs ] . addr . slot = slot ;
 addrs [ naddrs ] . addr . function = func ;
 addrs [ naddrs ] . vendor = vendor ;
 addrs [ naddrs ] . product = product ;
 naddrs ++ ;
 VIR_DEBUG ( "Got dev %d:%d:%d %x:%x" , bus , slot , func , vendor , product ) ;
 }
 VIR_FREE ( reply ) ;
 * retaddrs = addrs ;
 return naddrs ;
 error : VIR_FREE ( addrs ) ;
 VIR_FREE ( reply ) ;
 return - 1 ;
 }