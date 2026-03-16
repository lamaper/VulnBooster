static int qemuMonitorTextCommandNotFound ( const char * cmd , const char * reply ) {
 if ( STRPREFIX ( cmd , "info " ) ) {
 if ( strstr ( reply , "info version" ) ) return 1 ;
 }
 else {
 if ( strstr ( reply , "unknown command:" ) ) return 1 ;
 }
 return 0 ;
 }