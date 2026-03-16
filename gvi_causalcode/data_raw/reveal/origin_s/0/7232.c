static void dumpRoleMembership ( PGconn * conn ) {
 PGresult * res ;
 int i ;
 res = executeQuery ( conn , "SELECT ur.rolname AS roleid, " "um.rolname AS member, " "a.admin_option, " "ug.rolname AS grantor " "FROM pg_auth_members a " "LEFT JOIN pg_authid ur on ur.oid = a.roleid " "LEFT JOIN pg_authid um on um.oid = a.member " "LEFT JOIN pg_authid ug on ug.oid = a.grantor " "WHERE NOT (ur.rolname ~ '^pg_' AND um.rolname ~ '^pg_')" "ORDER BY 1,2,3" ) ;
 if ( PQntuples ( res ) > 0 ) fprintf ( OPF , "--\n-- Role memberships\n--\n\n" ) ;
 for ( i = 0 ;
 i < PQntuples ( res ) ;
 i ++ ) {
 char * roleid = PQgetvalue ( res , i , 0 ) ;
 char * member = PQgetvalue ( res , i , 1 ) ;
 char * option = PQgetvalue ( res , i , 2 ) ;
 fprintf ( OPF , "GRANT %s" , fmtId ( roleid ) ) ;
 fprintf ( OPF , " TO %s" , fmtId ( member ) ) ;
 if ( * option == 't' ) fprintf ( OPF , " WITH ADMIN OPTION" ) ;
 if ( ! PQgetisnull ( res , i , 3 ) ) {
 char * grantor = PQgetvalue ( res , i , 3 ) ;
 fprintf ( OPF , " GRANTED BY %s" , fmtId ( grantor ) ) ;
 }
 fprintf ( OPF , ";
\n" ) ;
 }
 PQclear ( res ) ;
 fprintf ( OPF , "\n\n" ) ;
 }