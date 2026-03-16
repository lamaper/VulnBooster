extern int as_mysql_suspend ( mysql_conn_t * mysql_conn , uint64_t old_db_inx , struct job_record * job_ptr ) {
 char * query = NULL ;
 int rc = SLURM_SUCCESS ;
 time_t submit_time ;
 uint64_t job_db_inx ;
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return ESLURM_DB_CONNECTION ;
 if ( job_ptr -> resize_time ) submit_time = job_ptr -> resize_time ;
 else submit_time = job_ptr -> details -> submit_time ;
 if ( ! job_ptr -> db_index ) {
 if ( ! ( job_ptr -> db_index = _get_db_index ( mysql_conn , submit_time , job_ptr -> job_id , job_ptr -> assoc_id ) ) ) {
 if ( as_mysql_job_start ( mysql_conn , job_ptr ) == SLURM_ERROR ) {
 error ( "couldn't suspend job %u" , job_ptr -> job_id ) ;
 return SLURM_SUCCESS ;
 }
 }
 }
 if ( IS_JOB_RESIZING ( job_ptr ) ) {
 if ( ! old_db_inx ) {
 error ( "No old db inx given for job %u cluster %s, " "can't update suspend table." , job_ptr -> job_id , mysql_conn -> cluster_name ) ;
 return SLURM_ERROR ;
 }
 job_db_inx = old_db_inx ;
 xstrfmtcat ( query , "update \"%s_%s\" set time_end=%d where " "job_db_inx=%" PRIu64 " && time_end=0;
" , mysql_conn -> cluster_name , suspend_table , ( int ) job_ptr -> suspend_time , job_db_inx ) ;
 }
 else job_db_inx = job_ptr -> db_index ;
 xstrfmtcat ( query , "update \"%s_%s\" set time_suspended=%d-time_suspended, " "state=%d where job_db_inx=%" PRIu64 ";
" , mysql_conn -> cluster_name , job_table , ( int ) job_ptr -> suspend_time , job_ptr -> job_state & JOB_STATE_BASE , job_db_inx ) ;
 if ( IS_JOB_SUSPENDED ( job_ptr ) ) xstrfmtcat ( query , "insert into \"%s_%s\" (job_db_inx, id_assoc, " "time_start, time_end) " "values (%" PRIu64 ", %u, %d, 0);
" , mysql_conn -> cluster_name , suspend_table , job_ptr -> db_index , job_ptr -> assoc_id , ( int ) job_ptr -> suspend_time ) ;
 else xstrfmtcat ( query , "update \"%s_%s\" set time_end=%d where " "job_db_inx=%" PRIu64 " && time_end=0;
" , mysql_conn -> cluster_name , suspend_table , ( int ) job_ptr -> suspend_time , job_ptr -> db_index ) ;
 if ( debug_flags & DEBUG_FLAG_DB_JOB ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 if ( rc != SLURM_ERROR ) {
 xstrfmtcat ( query , "update \"%s_%s\" set " "time_suspended=%u-time_suspended, " "state=%d where job_db_inx=%" PRIu64 " and time_end=0" , mysql_conn -> cluster_name , step_table , ( int ) job_ptr -> suspend_time , job_ptr -> job_state , job_ptr -> db_index ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 }
 return rc ;
 }