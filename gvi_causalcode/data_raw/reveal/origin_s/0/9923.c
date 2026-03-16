static void dumpDbRoleConfig ( PGconn * conn ) {
 PQExpBuffer buf = createPQExpBuffer ( ) ;
 PGresult * res ;
 int i ;
 printfPQExpBuffer ( buf , "SELECT rolname, datname, unnest(setconfig) " "FROM pg_db_role_setting, pg_authid, pg_database " "WHERE setrole = pg_authid.oid AND setdatabase = pg_database.oid" ) ;
 res = executeQuery ( conn , buf -> data ) ;
 if ( PQntuples ( res ) > 0 ) {
 fprintf ( OPF , "--\n-- Per-Database Role Settings \n--\n\n" ) ;
 for ( i = 0 ;
 i < PQntuples ( res ) ;
 i ++ ) {
 makeAlterConfigCommand ( conn , PQgetvalue ( res , i , 2 ) , "ROLE" , PQgetvalue ( res , i , 0 ) , "DATABASE" , PQgetvalue ( res , i , 1 ) ) ;
 }
 fprintf ( OPF , "\n\n" ) ;
 }
 PQclear ( res ) ;
 destroyPQExpBuffer ( buf ) ;
 }