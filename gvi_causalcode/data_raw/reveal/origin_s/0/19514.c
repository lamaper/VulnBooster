static void dropRoles ( PGconn * conn ) {
 PGresult * res ;
 int i_rolname ;
 int i ;
 if ( server_version >= 90600 ) res = executeQuery ( conn , "SELECT rolname " "FROM pg_authid " "WHERE rolname !~ '^pg_' " "ORDER BY 1" ) ;
 else if ( server_version >= 80100 ) res = executeQuery ( conn , "SELECT rolname " "FROM pg_authid " "ORDER BY 1" ) ;
 else res = executeQuery ( conn , "SELECT usename as rolname " "FROM pg_shadow " "UNION " "SELECT groname as rolname " "FROM pg_group " "ORDER BY 1" ) ;
 i_rolname = PQfnumber ( res , "rolname" ) ;
 if ( PQntuples ( res ) > 0 ) fprintf ( OPF , "--\n-- Drop roles\n--\n\n" ) ;
 for ( i = 0 ;
 i < PQntuples ( res ) ;
 i ++ ) {
 const char * rolename ;
 rolename = PQgetvalue ( res , i , i_rolname ) ;
 fprintf ( OPF , "DROP ROLE %s%s;
\n" , if_exists ? "IF EXISTS " : "" , fmtId ( rolename ) ) ;
 }
 PQclear ( res ) ;
 fprintf ( OPF , "\n\n" ) ;
 }