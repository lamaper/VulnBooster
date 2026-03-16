PGconn * connectToServer ( ClusterInfo * cluster , const char * db_name ) {
 PGconn * conn = get_db_conn ( cluster , db_name ) ;
 if ( conn == NULL || PQstatus ( conn ) != CONNECTION_OK ) {
 pg_log ( PG_REPORT , "connection to database failed: %s\n" , PQerrorMessage ( conn ) ) ;
 if ( conn ) PQfinish ( conn ) ;
 printf ( "Failure, exiting\n" ) ;
 exit ( 1 ) ;
 }
 return conn ;
 }