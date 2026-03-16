static void dropTablespaces ( PGconn * conn ) {
 PGresult * res ;
 int i ;
 res = executeQuery ( conn , "SELECT spcname " "FROM pg_catalog.pg_tablespace " "WHERE spcname !~ '^pg_' " "ORDER BY 1" ) ;
 if ( PQntuples ( res ) > 0 ) fprintf ( OPF , "--\n-- Drop tablespaces\n--\n\n" ) ;
 for ( i = 0 ;
 i < PQntuples ( res ) ;
 i ++ ) {
 char * spcname = PQgetvalue ( res , i , 0 ) ;
 fprintf ( OPF , "DROP TABLESPACE %s%s;
\n" , if_exists ? "IF EXISTS " : "" , fmtId ( spcname ) ) ;
 }
 PQclear ( res ) ;
 fprintf ( OPF , "\n\n" ) ;
 }