static bool GetQueryResult ( PGconn * conn , const char * progname ) {
 PGresult * result ;
 SetCancelConn ( conn ) ;
 while ( ( result = PQgetResult ( conn ) ) != NULL ) {
 if ( PQresultStatus ( result ) != PGRES_COMMAND_OK ) {
 char * sqlState = PQresultErrorField ( result , PG_DIAG_SQLSTATE ) ;
 fprintf ( stderr , _ ( "%s: vacuuming of database \"%s\" failed: %s" ) , progname , PQdb ( conn ) , PQerrorMessage ( conn ) ) ;
 if ( sqlState && strcmp ( sqlState , ERRCODE_UNDEFINED_TABLE ) != 0 ) {
 PQclear ( result ) ;
 return false ;
 }
 }
 PQclear ( result ) ;
 }
 ResetCancelConn ( ) ;
 return true ;
 }