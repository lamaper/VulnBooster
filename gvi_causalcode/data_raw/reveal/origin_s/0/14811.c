static void dbDisconnect ( char * host ) {
 verbose_msg ( "-- Disconnecting from %s...\n" , host ? host : "localhost" ) ;
 mysql_close ( mysql ) ;
 }