static void cmd_server ( const char * data ) {
 if ( * data != '\0' ) return ;
 if ( servers == NULL && lookup_servers == NULL && reconnects == NULL ) {
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_NO_CONNECTED_SERVERS ) ;
 }
 else {
 print_servers ( ) ;
 print_lookup_servers ( ) ;
 print_reconnects ( ) ;
 }
 signal_stop ( ) ;
 }