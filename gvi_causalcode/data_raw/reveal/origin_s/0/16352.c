static int qemudParseDriveAddReply ( const char * reply , virDomainDeviceDriveAddressPtr addr ) {
 char * s , * e ;
 if ( ! ( s = strstr ( reply , "OK " ) ) ) return - 1 ;
 s += 3 ;
 if ( STRPREFIX ( s , "bus " ) ) {
 s += strlen ( "bus " ) ;
 if ( virStrToLong_ui ( s , & e , 10 , & addr -> bus ) == - 1 ) {
 VIR_WARN ( "Unable to parse bus '%s'" , s ) ;
 return - 1 ;
 }
 if ( ! STRPREFIX ( e , ", " ) ) {
 VIR_WARN ( "Expected ', ' parsing drive_add reply '%s'" , s ) ;
 return - 1 ;
 }
 s = e + 2 ;
 }
 if ( ! STRPREFIX ( s , "unit " ) ) {
 VIR_WARN ( "Expected 'unit ' parsing drive_add reply '%s'" , s ) ;
 return - 1 ;
 }
 s += strlen ( "bus " ) ;
 if ( virStrToLong_ui ( s , & e , 10 , & addr -> unit ) == - 1 ) {
 VIR_WARN ( "Unable to parse unit number '%s'" , s ) ;
 return - 1 ;
 }
 return 0 ;
 }