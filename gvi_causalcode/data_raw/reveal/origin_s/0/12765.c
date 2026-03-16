void TSError ( const char * fmt , ... ) {
 va_list args ;
 if ( is_action_tag_set ( "deft" ) || is_action_tag_set ( "sdk_vbos_errors" ) ) {
 va_start ( args , fmt ) ;
 ErrorV ( fmt , args ) ;
 va_end ( args ) ;
 }
 va_start ( args , fmt ) ;
 Log : : va_error ( ( char * ) fmt , args ) ;
 va_end ( args ) ;
 }