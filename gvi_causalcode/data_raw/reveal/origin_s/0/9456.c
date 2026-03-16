static int qemuMonitorTextParsePciAddReply ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , const char * reply , virDomainDevicePCIAddress * addr ) {
 char * s , * e ;
 if ( ! ( s = strstr ( reply , "OK " ) ) ) return - 1 ;
 s += 3 ;
 if ( STRPREFIX ( s , "domain " ) ) {
 s += strlen ( "domain " ) ;
 if ( virStrToLong_ui ( s , & e , 10 , & addr -> domain ) == - 1 ) {
 VIR_WARN ( "Unable to parse domain number '%s'" , s ) ;
 return - 1 ;
 }
 if ( ! STRPREFIX ( e , ", " ) ) {
 VIR_WARN ( "Expected ', ' parsing pci_add reply '%s'" , s ) ;
 return - 1 ;
 }
 s = e + 2 ;
 }
 if ( ! STRPREFIX ( s , "bus " ) ) {
 VIR_WARN ( "Expected 'bus ' parsing pci_add reply '%s'" , s ) ;
 return - 1 ;
 }
 s += strlen ( "bus " ) ;
 if ( virStrToLong_ui ( s , & e , 10 , & addr -> bus ) == - 1 ) {
 VIR_WARN ( "Unable to parse bus number '%s'" , s ) ;
 return - 1 ;
 }
 if ( ! STRPREFIX ( e , ", " ) ) {
 VIR_WARN ( "Expected ', ' parsing pci_add reply '%s'" , s ) ;
 return - 1 ;
 }
 s = e + 2 ;
 if ( ! STRPREFIX ( s , "slot " ) ) {
 VIR_WARN ( "Expected 'slot ' parsing pci_add reply '%s'" , s ) ;
 return - 1 ;
 }
 s += strlen ( "slot " ) ;
 if ( virStrToLong_ui ( s , & e , 10 , & addr -> slot ) == - 1 ) {
 VIR_WARN ( "Unable to parse slot number '%s'" , s ) ;
 return - 1 ;
 }
 return 0 ;
 }