static uint64_t _get_db_index ( mysql_conn_t * mysql_conn , time_t submit , uint32_t jobid , uint32_t associd ) {
 MYSQL_RES * result = NULL ;
 MYSQL_ROW row ;
 uint64_t db_index = 0 ;
 char * query = xstrdup_printf ( "select job_db_inx from \"%s_%s\" where " "time_submit=%d and id_job=%u " "and id_assoc=%u" , mysql_conn -> cluster_name , job_table , ( int ) submit , jobid , associd ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 return 0 ;
 }
 xfree ( query ) ;
 row = mysql_fetch_row ( result ) ;
 if ( ! row ) {
 mysql_free_result ( result ) ;
 debug4 ( "We can't get a db_index for this combo, " "time_submit=%d and id_job=%u and id_assoc=%u. " "We must not have heard about the start yet, " "no big deal, we will get one right after this." , ( int ) submit , jobid , associd ) ;
 return 0 ;
 }
 db_index = slurm_atoull ( row [ 0 ] ) ;
 mysql_free_result ( result ) ;
 return db_index ;
 }