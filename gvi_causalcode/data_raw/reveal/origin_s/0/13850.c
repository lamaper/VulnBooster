static void ExecuteSqlCommand ( ArchiveHandle * AH , const char * qry , const char * desc ) {
 PGconn * conn = AH -> connection ;
 PGresult * res ;
 char errStmt [ DB_MAX_ERR_STMT ] ;


 switch ( PQresultStatus ( res ) ) {
 case PGRES_COMMAND_OK : case PGRES_TUPLES_OK : case PGRES_EMPTY_QUERY : break ;
 case PGRES_COPY_IN : AH -> pgCopyIn = true ;
 break ;
 default : strncpy ( errStmt , qry , DB_MAX_ERR_STMT ) ;
 if ( errStmt [ DB_MAX_ERR_STMT - 1 ] != '\0' ) {
 errStmt [ DB_MAX_ERR_STMT - 4 ] = '.' ;
 errStmt [ DB_MAX_ERR_STMT - 3 ] = '.' ;
 errStmt [ DB_MAX_ERR_STMT - 2 ] = '.' ;
 errStmt [ DB_MAX_ERR_STMT - 1 ] = '\0' ;
 }
 warn_or_exit_horribly ( AH , modulename , "%s: %s Command was: %s\n" , desc , PQerrorMessage ( conn ) , errStmt ) ;
 break ;
 }
 PQclear ( res ) ;
 }