static void dumpDatabaseConfig ( PGconn * conn , const char * dbname ) {
 PQExpBuffer buf = createPQExpBuffer ( ) ;
 int count = 1 ;
 for ( ;
 ;
 ) {
 PGresult * res ;
 if ( server_version >= 90000 ) printfPQExpBuffer ( buf , "SELECT setconfig[%d] FROM pg_db_role_setting WHERE " "setrole = 0 AND setdatabase = (SELECT oid FROM pg_database WHERE datname = " , count ) ;
 else printfPQExpBuffer ( buf , "SELECT datconfig[%d] FROM pg_database WHERE datname = " , count ) ;
 appendStringLiteralConn ( buf , dbname , conn ) ;
 if ( server_version >= 90000 ) appendPQExpBuffer ( buf , ")" ) ;
 res = executeQuery ( conn , buf -> data ) ;
 if ( PQntuples ( res ) == 1 && ! PQgetisnull ( res , 0 , 0 ) ) {
 makeAlterConfigCommand ( conn , PQgetvalue ( res , 0 , 0 ) , "DATABASE" , dbname , NULL , NULL ) ;
 PQclear ( res ) ;
 count ++ ;
 }
 else {
 PQclear ( res ) ;
 break ;
 }
 }
 destroyPQExpBuffer ( buf ) ;
 }