static void check_for_prepared_transactions ( ClusterInfo * cluster ) {
 PGresult * res ;
 PGconn * conn = connectToServer ( cluster , "template1" ) ;
 prep_status ( "Checking for prepared transactions" ) ;
 res = executeQueryOrDie ( conn , "SELECT * " "FROM pg_catalog.pg_prepared_xacts" ) ;
 if ( PQntuples ( res ) != 0 ) pg_fatal ( "The %s cluster contains prepared transactions\n" , CLUSTER_NAME ( cluster ) ) ;
 PQclear ( res ) ;
 PQfinish ( conn ) ;
 check_ok ( ) ;
 }