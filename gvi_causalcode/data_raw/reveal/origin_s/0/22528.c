extern int as_mysql_step_complete ( mysql_conn_t * mysql_conn , struct step_record * step_ptr ) {
 time_t now ;
 uint16_t comp_status ;
 int tasks = 0 ;
 struct jobacctinfo * jobacct = ( struct jobacctinfo * ) step_ptr -> jobacct ;
 char * query = NULL ;
 int rc = SLURM_SUCCESS ;
 uint32_t exit_code = 0 ;
 time_t submit_time ;
 if ( ! step_ptr -> job_ptr -> db_index && ( ( ! step_ptr -> job_ptr -> details || ! step_ptr -> job_ptr -> details -> submit_time ) && ! step_ptr -> job_ptr -> resize_time ) ) {
 error ( "as_mysql_step_complete: " "Not inputing this job, it has no submit time." ) ;
 return SLURM_ERROR ;
 }
 if ( step_ptr -> job_ptr -> resize_time ) submit_time = step_ptr -> job_ptr -> resize_time ;
 else submit_time = step_ptr -> job_ptr -> details -> submit_time ;
 if ( check_connection ( mysql_conn ) != SLURM_SUCCESS ) return ESLURM_DB_CONNECTION ;
 if ( slurmdbd_conf ) {
 now = step_ptr -> job_ptr -> end_time ;
 if ( step_ptr -> job_ptr -> details ) tasks = step_ptr -> job_ptr -> details -> num_tasks ;
 else tasks = step_ptr -> cpu_count ;
 }
 else if ( step_ptr -> step_id == SLURM_BATCH_SCRIPT ) {
 now = time ( NULL ) ;
 tasks = 1 ;
 }
 else {
 now = time ( NULL ) ;
 if ( ! step_ptr -> step_layout || ! step_ptr -> step_layout -> task_cnt ) {
 if ( step_ptr -> cpu_count ) tasks = step_ptr -> cpu_count ;
 else {
 if ( ( tasks = slurmdb_find_tres_count_in_string ( step_ptr -> tres_alloc_str , TRES_CPU ) ) == INFINITE64 ) {
 if ( ( tasks = slurmdb_find_tres_count_in_string ( step_ptr -> job_ptr -> tres_alloc_str , TRES_CPU ) ) == INFINITE64 ) tasks = step_ptr -> job_ptr -> total_nodes ;
 }
 }
 }
 else tasks = step_ptr -> step_layout -> task_cnt ;
 }
 exit_code = step_ptr -> exit_code ;
 comp_status = step_ptr -> state & JOB_STATE_BASE ;
 if ( comp_status < JOB_COMPLETE ) {
 if ( WIFSIGNALED ( exit_code ) ) {
 comp_status = JOB_CANCELLED ;
 }
 else if ( exit_code ) comp_status = JOB_FAILED ;
 else {
 step_ptr -> requid = - 1 ;
 comp_status = JOB_COMPLETE ;
 }
 }
 if ( ! step_ptr -> job_ptr -> db_index ) {
 if ( ! ( step_ptr -> job_ptr -> db_index = _get_db_index ( mysql_conn , submit_time , step_ptr -> job_ptr -> job_id , step_ptr -> job_ptr -> assoc_id ) ) ) {
 if ( as_mysql_job_start ( mysql_conn , step_ptr -> job_ptr ) == SLURM_ERROR ) {
 error ( "couldn't add job %u " "at step completion" , step_ptr -> job_ptr -> job_id ) ;
 return SLURM_SUCCESS ;
 }
 }
 }
 query = xstrdup_printf ( "update \"%s_%s\" set time_end=%d, state=%u, " "kill_requid=%d, exit_code=%d" , mysql_conn -> cluster_name , step_table , ( int ) now , comp_status , step_ptr -> requid , exit_code ) ;
 if ( jobacct ) {
 double ave_vsize = NO_VAL , ave_rss = NO_VAL , ave_pages = NO_VAL ;
 double ave_disk_read = ( double ) NO_VAL ;
 double ave_disk_write = ( double ) NO_VAL ;
 double ave_cpu = ( double ) NO_VAL ;
 if ( tasks > 0 ) {
 ave_vsize = ( double ) jobacct -> tot_vsize ;
 ave_vsize /= ( double ) tasks ;
 ave_rss = ( double ) jobacct -> tot_rss ;
 ave_rss /= ( double ) tasks ;
 ave_pages = ( double ) jobacct -> tot_pages ;
 ave_pages /= ( double ) tasks ;
 ave_cpu = ( double ) jobacct -> tot_cpu ;
 ave_cpu /= ( double ) tasks ;
 ave_disk_read = ( double ) jobacct -> tot_disk_read ;
 ave_disk_read /= ( double ) tasks ;
 ave_disk_write = ( double ) jobacct -> tot_disk_write ;
 ave_disk_write /= ( double ) tasks ;
 }
 xstrfmtcat ( query , ", user_sec=%u, user_usec=%u, " "sys_sec=%u, sys_usec=%u, " "max_disk_read=%f, max_disk_read_task=%u, " "max_disk_read_node=%u, ave_disk_read=%f, " "max_disk_write=%f, max_disk_write_task=%u, " "max_disk_write_node=%u, ave_disk_write=%f, " "max_vsize=%" PRIu64 ", max_vsize_task=%u, " "max_vsize_node=%u, ave_vsize=%f, " "max_rss=%" PRIu64 ", max_rss_task=%u, " "max_rss_node=%u, ave_rss=%f, " "max_pages=%" PRIu64 ", max_pages_task=%u, " "max_pages_node=%u, ave_pages=%f, " "min_cpu=%u, min_cpu_task=%u, " "min_cpu_node=%u, ave_cpu=%f, " "act_cpufreq=%u, consumed_energy=%" PRIu64 "" , jobacct -> user_cpu_sec , jobacct -> user_cpu_usec , jobacct -> sys_cpu_sec , jobacct -> sys_cpu_usec , jobacct -> max_disk_read , jobacct -> max_disk_read_id . taskid , jobacct -> max_disk_read_id . nodeid , ave_disk_read , jobacct -> max_disk_write , jobacct -> max_disk_write_id . taskid , jobacct -> max_disk_write_id . nodeid , ave_disk_write , jobacct -> max_vsize , jobacct -> max_vsize_id . taskid , jobacct -> max_vsize_id . nodeid , ave_vsize , jobacct -> max_rss , jobacct -> max_rss_id . taskid , jobacct -> max_rss_id . nodeid , ave_rss , jobacct -> max_pages , jobacct -> max_pages_id . taskid , jobacct -> max_pages_id . nodeid , ave_pages , jobacct -> min_cpu , jobacct -> min_cpu_id . taskid , jobacct -> min_cpu_id . nodeid , ave_cpu , jobacct -> act_cpufreq , jobacct -> energy . consumed_energy ) ;
 }
 xstrfmtcat ( query , " where job_db_inx=%" PRIu64 " and id_step=%d" , step_ptr -> job_ptr -> db_index , step_ptr -> step_id ) ;
 if ( debug_flags & DEBUG_FLAG_DB_STEP ) DB_DEBUG ( mysql_conn -> conn , "query\n%s" , query ) ;
 rc = mysql_db_query ( mysql_conn , query ) ;
 xfree ( query ) ;
 return rc ;
 }