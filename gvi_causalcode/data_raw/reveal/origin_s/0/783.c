static void check_for_pg_role_prefix ( ClusterInfo * cluster ) {
 PGresult * res ;
 PGconn * conn = connectToServer ( cluster , "template1" ) ;
 prep_status ( "Checking for roles starting with 'pg_'" ) ;
 res = executeQueryOrDie ( conn , "SELECT * " "FROM pg_catalog.pg_roles " "WHERE rolname ~ '^pg_'" ) ;
 if ( PQntuples ( res ) != 0 ) pg_fatal ( "The %s cluster contains roles starting with 'pg_'\n" , CLUSTER_NAME ( cluster ) ) ;
 PQclear ( res ) ;
 PQfinish ( conn ) ;
 check_ok ( ) ;
 }