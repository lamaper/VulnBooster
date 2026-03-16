static void set_frozenxids ( bool minmxid_only ) {
 int dbnum ;
 PGconn * conn , * conn_template1 ;
 PGresult * dbres ;
 int ntups ;
 int i_datname ;
 int i_datallowconn ;
 if ( ! minmxid_only ) prep_status ( "Setting frozenxid and minmxid counters in new cluster" ) ;
 else prep_status ( "Setting minmxid counter in new cluster" ) ;
 conn_template1 = connectToServer ( & new_cluster , "template1" ) ;
 if ( ! minmxid_only ) PQclear ( executeQueryOrDie ( conn_template1 , "UPDATE pg_catalog.pg_database " "SET datfrozenxid = '%u'" , old_cluster . controldata . chkpnt_nxtxid ) ) ;
 PQclear ( executeQueryOrDie ( conn_template1 , "UPDATE pg_catalog.pg_database " "SET datminmxid = '%u'" , old_cluster . controldata . chkpnt_nxtmulti ) ) ;
 dbres = executeQueryOrDie ( conn_template1 , "SELECT datname, datallowconn " "FROM pg_catalog.pg_database" ) ;
 i_datname = PQfnumber ( dbres , "datname" ) ;
 i_datallowconn = PQfnumber ( dbres , "datallowconn" ) ;
 ntups = PQntuples ( dbres ) ;
 for ( dbnum = 0 ;
 dbnum < ntups ;
 dbnum ++ ) {
 char * datname = PQgetvalue ( dbres , dbnum , i_datname ) ;
 char * datallowconn = PQgetvalue ( dbres , dbnum , i_datallowconn ) ;
 if ( strcmp ( datallowconn , "f" ) == 0 ) PQclear ( executeQueryOrDie ( conn_template1 , "ALTER DATABASE %s ALLOW_CONNECTIONS = true" , quote_identifier ( datname ) ) ) ;
 conn = connectToServer ( & new_cluster , datname ) ;
 if ( ! minmxid_only ) PQclear ( executeQueryOrDie ( conn , "UPDATE pg_catalog.pg_class " "SET relfrozenxid = '%u' " "WHERE relkind IN ('r', 'm', 't')" , old_cluster . controldata . chkpnt_nxtxid ) ) ;
 PQclear ( executeQueryOrDie ( conn , "UPDATE pg_catalog.pg_class " "SET relminmxid = '%u' " "WHERE relkind IN ('r', 'm', 't')" , old_cluster . controldata . chkpnt_nxtmulti ) ) ;
 PQfinish ( conn ) ;
 if ( strcmp ( datallowconn , "f" ) == 0 ) PQclear ( executeQueryOrDie ( conn_template1 , "ALTER DATABASE %s ALLOW_CONNECTIONS = false" , quote_identifier ( datname ) ) ) ;
 }
 PQclear ( dbres ) ;
 PQfinish ( conn_template1 ) ;
 check_ok ( ) ;
 }