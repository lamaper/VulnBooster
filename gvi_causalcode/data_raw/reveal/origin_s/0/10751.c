static void executeCommand ( PGconn * conn , const char * query ) {
 PGresult * res ;
 if ( verbose ) fprintf ( stderr , _ ( "%s: executing %s\n" ) , progname , query ) ;
 res = PQexec ( conn , query ) ;
 if ( ! res || PQresultStatus ( res ) != PGRES_COMMAND_OK ) {
 fprintf ( stderr , _ ( "%s: query failed: %s" ) , progname , PQerrorMessage ( conn ) ) ;
 fprintf ( stderr , _ ( "%s: query was: %s\n" ) , progname , query ) ;
 PQfinish ( conn ) ;
 exit_nicely ( 1 ) ;
 }
 PQclear ( res ) ;
 }