static void prepare_new_databases ( void ) {
 set_frozenxids ( false ) ;
 prep_status ( "Restoring global objects in the new cluster" ) ;
 exec_prog ( UTILITY_LOG_FILE , NULL , true , "\"%s/psql\" " EXEC_PSQL_ARGS " %s -f \"%s\"" , new_cluster . bindir , cluster_conn_opts ( & new_cluster ) , GLOBALS_DUMP_FILE ) ;
 check_ok ( ) ;
 get_db_and_rel_infos ( & new_cluster ) ;
 }