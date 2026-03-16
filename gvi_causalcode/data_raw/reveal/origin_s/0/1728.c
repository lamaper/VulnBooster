extern int as_mysql_flush_jobs_on_cluster ( mysql_conn_t * mysql_conn , time_t event_time ) {
 int rc = SLURM_SUCCESS ;
 MYSQL_RES * result = NULL ;
 MYSQL_ROW row ;
 char * query = NULL ;
 char * id_char = NULL ;
 char * suspended_char = NULL ;
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return ESLURM_DB_CONNECTION ;
 query = xstrdup_printf ( "select distinct t1.job_db_inx, t1.state from \"%s_%s\" " "as t1 where t1.time_end=0;
" , mysql_conn -> cluster_name , job_table ) ;
 if ( debug_flags & DEBUG_FLAG_DB_JOB ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 if ( ! ( result = mysql_db_query_ret ( mysql_conn , query , 0 ) ) ) {
 xfree ( query ) ;
 return SLURM_ERROR ;
 }
 xfree ( query ) ;
 while ( ( row = mysql_fetch_row ( result ) ) ) {
 int state = slurm_atoul ( row [ 1 ] ) ;
 if ( state == JOB_SUSPENDED ) {
 if ( suspended_char ) xstrfmtcat ( suspended_char , ", %s" , row [ 0 ] ) ;
 else xstrfmtcat ( suspended_char , "job_db_inx in (%s" , row [ 0 ] ) ;
 }
 if ( id_char ) xstrfmtcat ( id_char , ", %s" , row [ 0 ] ) ;
 else xstrfmtcat ( id_char , "job_db_inx in (%s" , row [ 0 ] ) ;
 }
 mysql_free_result ( result ) ;
 if ( suspended_char ) {
 xstrfmtcat ( suspended_char , ")" ) ;
 xstrfmtcat ( query , "update \"%s_%s\" set " "time_suspended=%ld-time_suspended " "where %s;
" , mysql_conn -> cluster_name , job_table , event_time , suspended_char ) ;
 xstrfmtcat ( query , "update \"%s_%s\" set " "time_suspended=%ld-time_suspended " "where %s;
" , mysql_conn -> cluster_name , step_table , event_time , suspended_char ) ;
 xstrfmtcat ( query , "update \"%s_%s\" set time_end=%ld where (%s) " "&& time_end=0;
" , mysql_conn -> cluster_name , suspend_table , event_time , suspended_char ) ;
 xfree ( suspended_char ) ;
 }
 if ( id_char ) {
 xstrfmtcat ( id_char , ")" ) ;
 xstrfmtcat ( query , "update \"%s_%s\" set state=%d, " "time_end=%ld where %s;
" , mysql_conn -> cluster_name , job_table , JOB_CANCELLED , event_time , id_char ) ;
 xstrfmtcat ( query , "update \"%s_%s\" set state=%d, " "time_end=%ld where %s;
" , mysql_conn -> cluster_name , step_table , JOB_CANCELLED , event_time , id_char ) ;
 xfree ( id_char ) ;
 }
 if ( query ) {
 if ( debug_flags & DEBUG_FLAG_DB_JOB ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 }
 return rc ;
 }