static void dropDBs ( PGconn * conn ) {
 PGresult * res ;
 int i ;
 if ( server_version >= 70100 ) res = executeQuery ( conn , "SELECT datname " "FROM pg_database d " "WHERE datallowconn ORDER BY 1" ) ;
 else res = executeQuery ( conn , "SELECT datname " "FROM pg_database d " "ORDER BY 1" ) ;
 if ( PQntuples ( res ) > 0 ) fprintf ( OPF , "--\n-- Drop databases\n--\n\n" ) ;
 for ( i = 0 ;
 i < PQntuples ( res ) ;
 i ++ ) {
 char * dbname = PQgetvalue ( res , i , 0 ) ;
 if ( strcmp ( dbname , "template1" ) != 0 && strcmp ( dbname , "postgres" ) != 0 ) {
 fprintf ( OPF , "DROP DATABASE %s%s;
\n" , if_exists ? "IF EXISTS " : "" , fmtId ( dbname ) ) ;
 }
 }
 PQclear ( res ) ;
 fprintf ( OPF , "\n\n" ) ;
 }