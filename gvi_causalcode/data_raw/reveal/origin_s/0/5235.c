PGresult * executeQueryOrDie ( PGconn * conn , const char * fmt , ... ) {
 static char query [ QUERY_ALLOC ] ;
 va_list args ;
 PGresult * result ;
 ExecStatusType status ;
 va_start ( args , fmt ) ;
 vsnprintf ( query , sizeof ( query ) , fmt , args ) ;
 va_end ( args ) ;
 pg_log ( PG_VERBOSE , "executing: %s\n" , query ) ;
 result = PQexec ( conn , query ) ;
 status = PQresultStatus ( result ) ;
 if ( ( status != PGRES_TUPLES_OK ) && ( status != PGRES_COMMAND_OK ) ) {
 pg_log ( PG_REPORT , "SQL command failed\n%s\n%s\n" , query , PQerrorMessage ( conn ) ) ;
 PQclear ( result ) ;
 PQfinish ( conn ) ;
 printf ( "Failure, exiting\n" ) ;
 exit ( 1 ) ;
 }
 else return result ;
 }