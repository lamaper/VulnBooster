static void prepare_new_cluster ( void ) {
 prep_status ( "Analyzing all rows in the new cluster" ) ;
 exec_prog ( UTILITY_LOG_FILE , NULL , true , "\"%s/vacuumdb\" %s --all --analyze %s" , new_cluster . bindir , cluster_conn_opts ( & new_cluster ) , log_opts . verbose ? "--verbose" : "" ) ;
 check_ok ( ) ;
 prep_status ( "Freezing all rows on the new cluster" ) ;
 exec_prog ( UTILITY_LOG_FILE , NULL , true , "\"%s/vacuumdb\" %s --all --freeze %s" , new_cluster . bindir , cluster_conn_opts ( & new_cluster ) , log_opts . verbose ? "--verbose" : "" ) ;
 check_ok ( ) ;
 }