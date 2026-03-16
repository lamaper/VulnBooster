static void dumpUserConfig ( PGconn * conn , const char * username ) {
 PQExpBuffer buf = createPQExpBuffer ( ) ;
 int count = 1 ;
 for ( ;
 ;
 ) {
 PGresult * res ;
 if ( server_version >= 90000 ) printfPQExpBuffer ( buf , "SELECT setconfig[%d] FROM pg_db_role_setting WHERE " "setdatabase = 0 AND setrole = " "(SELECT oid FROM pg_authid WHERE rolname = " , count ) ;
 else if ( server_version >= 80100 ) printfPQExpBuffer ( buf , "SELECT rolconfig[%d] FROM pg_authid WHERE rolname = " , count ) ;
 else printfPQExpBuffer ( buf , "SELECT useconfig[%d] FROM pg_shadow WHERE usename = " , count ) ;
 appendStringLiteralConn ( buf , username , conn ) ;
 if ( server_version >= 90000 ) appendPQExpBufferChar ( buf , ')' ) ;
 res = executeQuery ( conn , buf -> data ) ;
 if ( PQntuples ( res ) == 1 && ! PQgetisnull ( res , 0 , 0 ) ) {
 makeAlterConfigCommand ( conn , PQgetvalue ( res , 0 , 0 ) , "ROLE" , username , NULL , NULL ) ;
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