static void copy_clog_xlog_xid ( void ) {
 copy_subdir_files ( "pg_clog" ) ;
 prep_status ( "Setting next transaction ID and epoch for new cluster" ) ;
 exec_prog ( UTILITY_LOG_FILE , NULL , true , "\"%s/pg_resetxlog\" -f -x %u \"%s\"" , new_cluster . bindir , old_cluster . controldata . chkpnt_nxtxid , new_cluster . pgdata ) ;
 exec_prog ( UTILITY_LOG_FILE , NULL , true , "\"%s/pg_resetxlog\" -f -e %u \"%s\"" , new_cluster . bindir , old_cluster . controldata . chkpnt_nxtepoch , new_cluster . pgdata ) ;
 exec_prog ( UTILITY_LOG_FILE , NULL , true , "\"%s/pg_resetxlog\" -f -c %u,%u \"%s\"" , new_cluster . bindir , old_cluster . controldata . chkpnt_nxtxid , old_cluster . controldata . chkpnt_nxtxid , new_cluster . pgdata ) ;
 check_ok ( ) ;
 if ( old_cluster . controldata . cat_ver >= MULTIXACT_FORMATCHANGE_CAT_VER && new_cluster . controldata . cat_ver >= MULTIXACT_FORMATCHANGE_CAT_VER ) {
 copy_subdir_files ( "pg_multixact/offsets" ) ;
 copy_subdir_files ( "pg_multixact/members" ) ;
 prep_status ( "Setting next multixact ID and offset for new cluster" ) ;
 exec_prog ( UTILITY_LOG_FILE , NULL , true , "\"%s/pg_resetxlog\" -O %u -m %u,%u \"%s\"" , new_cluster . bindir , old_cluster . controldata . chkpnt_nxtmxoff , old_cluster . controldata . chkpnt_nxtmulti , old_cluster . controldata . chkpnt_oldstMulti , new_cluster . pgdata ) ;
 check_ok ( ) ;
 }
 else if ( new_cluster . controldata . cat_ver >= MULTIXACT_FORMATCHANGE_CAT_VER ) {
 remove_new_subdir ( "pg_multixact/offsets" , false ) ;
 prep_status ( "Setting oldest multixact ID on new cluster" ) ;
 exec_prog ( UTILITY_LOG_FILE , NULL , true , "\"%s/pg_resetxlog\" -m %u,%u \"%s\"" , new_cluster . bindir , old_cluster . controldata . chkpnt_nxtmulti + 1 , old_cluster . controldata . chkpnt_nxtmulti , new_cluster . pgdata ) ;
 check_ok ( ) ;
 }
 prep_status ( "Resetting WAL archives" ) ;
 exec_prog ( UTILITY_LOG_FILE , NULL , true , "\"%s/pg_resetxlog\" -l 00000001%s \"%s\"" , new_cluster . bindir , old_cluster . controldata . nextxlogfile + 8 , new_cluster . pgdata ) ;
 check_ok ( ) ;
 }