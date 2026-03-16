static void nbd_export_closed ( NBDExport * exp ) {
 assert ( state == TERMINATING ) ;
 state = TERMINATED ;
 }