static void init_slot ( ParallelSlot * slot , PGconn * conn , const char * progname ) {
 slot -> connection = conn ;
 slot -> isFree = true ;
 slot -> sock = PQsocket ( conn ) ;
 if ( slot -> sock < 0 ) {
 fprintf ( stderr , _ ( "%s: invalid socket: %s" ) , progname , PQerrorMessage ( conn ) ) ;
 exit ( 1 ) ;
 }
 }