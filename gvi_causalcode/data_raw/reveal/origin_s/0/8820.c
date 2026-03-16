void proto_report_dissector_bug ( const char * message ) {
 if ( getenv ( "WIRESHARK_ABORT_ON_DISSECTOR_BUG" ) != NULL ) abort ( ) ;
 else THROW_MESSAGE ( DissectorError , message ) ;
 }