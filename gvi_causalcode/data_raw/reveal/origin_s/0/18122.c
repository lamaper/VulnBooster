inline static void _slurm_rpc_kill_job ( slurm_msg_t * msg ) {
 static int active_rpc_cnt = 0 ;
 DEF_TIMERS ;
 job_step_kill_msg_t * kill ;
 slurmctld_lock_t fed_job_read_lock = {
 NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK , READ_LOCK }
 ;
 slurmctld_lock_t lock = {
 READ_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , READ_LOCK }
 ;
 uid_t uid ;
 int cc ;
 kill = ( job_step_kill_msg_t * ) msg -> data ;
 uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 lock_slurmctld ( fed_job_read_lock ) ;
 if ( fed_mgr_fed_rec ) {
 uint32_t job_id , origin_id ;
 struct job_record * job_ptr ;
 slurmdb_cluster_rec_t * origin ;
 job_id = strtol ( kill -> sjob_id , NULL , 10 ) ;
 origin_id = fed_mgr_get_cluster_id ( job_id ) ;
 origin = fed_mgr_get_cluster_by_id ( origin_id ) ;
 if ( origin && origin -> fed . send && ( ( ( slurm_persist_conn_t * ) origin -> fed . send ) -> fd != - 1 ) && ( origin != fed_mgr_cluster_rec ) && ( ! ( job_ptr = find_job_record ( job_id ) ) || ( job_ptr && job_ptr -> fed_details && ( job_ptr -> fed_details -> cluster_lock != fed_mgr_cluster_rec -> fed . id ) ) ) ) {
 slurmdb_cluster_rec_t * dst = fed_mgr_get_cluster_by_id ( origin_id ) ;
 if ( ! dst ) {
 error ( "couldn't find cluster by cluster id %d" , origin_id ) ;
 slurm_send_rc_msg ( msg , SLURM_ERROR ) ;
 }
 else {
 slurm_send_reroute_msg ( msg , dst ) ;
 info ( "%s: REQUEST_KILL_JOB job %s uid %d routed to %s" , __func__ , kill -> sjob_id , uid , dst -> name ) ;
 }
 unlock_slurmctld ( fed_job_read_lock ) ;
 return ;
 }
 }
 unlock_slurmctld ( fed_job_read_lock ) ;
 START_TIMER ;
 info ( "%s: REQUEST_KILL_JOB job %s uid %d" , __func__ , kill -> sjob_id , uid ) ;
 _throttle_start ( & active_rpc_cnt ) ;
 lock_slurmctld ( lock ) ;
 if ( kill -> sibling ) {
 uint32_t job_id = strtol ( kill -> sjob_id , NULL , 10 ) ;
 cc = fed_mgr_remove_active_sibling ( job_id , kill -> sibling ) ;
 }
 else {
 cc = job_str_signal ( kill -> sjob_id , kill -> signal , kill -> flags , uid , 0 ) ;
 }
 unlock_slurmctld ( lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 if ( cc == ESLURM_ALREADY_DONE ) {
 debug2 ( "%s: job_str_signal() job %s sig %d returned %s" , __func__ , kill -> sjob_id , kill -> signal , slurm_strerror ( cc ) ) ;
 }
 else if ( cc != SLURM_SUCCESS ) {
 info ( "%s: job_str_signal() job %s sig %d returned %s" , __func__ , kill -> sjob_id , kill -> signal , slurm_strerror ( cc ) ) ;
 }
 else {
 slurmctld_diag_stats . jobs_canceled ++ ;
 }
 slurm_send_rc_msg ( msg , cc ) ;
 END_TIMER2 ( "_slurm_rpc_kill_job" ) ;
 }