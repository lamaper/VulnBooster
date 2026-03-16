static void _slurm_rpc_complete_batch_script ( slurm_msg_t * msg , bool * run_scheduler , bool running_composite ) {
 static int active_rpc_cnt = 0 ;
 int error_code = SLURM_SUCCESS , i ;
 DEF_TIMERS ;
 complete_batch_script_msg_t * comp_msg = ( complete_batch_script_msg_t * ) msg -> data ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 bool job_requeue = false ;
 bool dump_job = false , dump_node = false ;
 struct job_record * job_ptr = NULL ;
 char * msg_title = "node(s)" ;
 char * nodes = comp_msg -> node_name ;

 memset ( & block_desc , 0 , sizeof ( update_block_msg_t ) ) ;

 debug2 ( "Processing RPC: REQUEST_COMPLETE_BATCH_SCRIPT from " "uid=%u JobId=%u" , uid , comp_msg -> job_id ) ;
 if ( ! validate_slurm_user ( uid ) ) {
 error ( "A non superuser %u tried to complete batch job %u" , uid , comp_msg -> job_id ) ;
 END_TIMER2 ( "_slurm_rpc_complete_batch_script" ) ;
 return ;
 }
 if ( ! running_composite ) {
 _throttle_start ( & active_rpc_cnt ) ;
 lock_slurmctld ( job_write_lock ) ;
 }
 job_ptr = find_job_record ( comp_msg -> job_id ) ;
 if ( job_ptr && job_ptr -> batch_host && comp_msg -> node_name && xstrcmp ( job_ptr -> batch_host , comp_msg -> node_name ) ) {
 error ( "Batch completion for job %u sent from wrong node " "(%s rather than %s). " "Was the job requeued due to node failure?" , comp_msg -> job_id , comp_msg -> node_name , job_ptr -> batch_host ) ;
 if ( ! running_composite ) {
 unlock_slurmctld ( job_write_lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 }
 slurm_send_rc_msg ( msg , error_code ) ;
 return ;
 }
 if ( association_based_accounting && job_ptr && ( job_ptr -> job_state != JOB_PENDING ) ) {
 struct step_record batch_step ;
 memset ( & batch_step , 0 , sizeof ( struct step_record ) ) ;
 batch_step . job_ptr = job_ptr ;
 batch_step . step_id = SLURM_BATCH_SCRIPT ;
 batch_step . jobacct = comp_msg -> jobacct ;
 batch_step . exit_code = comp_msg -> job_rc ;


 if ( node_name2bitmap ( batch_step . gres , false , & batch_step . step_node_bitmap ) != 0 ) {
 error ( "%s: job %u has invalide node list (%s)" , __func__ , job_ptr -> job_id , batch_step . gres ) ;
 }
 batch_step . requid = - 1 ;
 batch_step . start_time = job_ptr -> start_time ;
 batch_step . name = "batch" ;
 batch_step . select_jobinfo = job_ptr -> select_jobinfo ;
 step_set_alloc_tres ( & batch_step , 1 , false , false ) ;
 jobacct_storage_g_step_start ( acct_db_conn , & batch_step ) ;
 jobacct_storage_g_step_complete ( acct_db_conn , & batch_step ) ;
 FREE_NULL_BITMAP ( batch_step . step_node_bitmap ) ;
 xfree ( batch_step . tres_alloc_str ) ;
 }

 msg_title = "front_end" ;

 info ( "slurmd error running JobId=%u from %s=%s: %s" , comp_msg -> job_id , msg_title , nodes , slurm_strerror ( comp_msg -> slurm_rc ) ) ;
 comp_msg -> slurm_rc = SLURM_SUCCESS ;

 else if ( comp_msg -> slurm_rc == ESLURM_RESERVATION_NOT_USABLE ) {
 error ( "ALPS reservation for JobId %u failed: %s" , comp_msg -> job_id , slurm_strerror ( comp_msg -> slurm_rc ) ) ;
 dump_job = job_requeue = true ;

 else if ( ( comp_msg -> slurm_rc == SLURM_COMMUNICATIONS_SEND_ERROR ) || ( comp_msg -> slurm_rc == ESLURM_USER_ID_MISSING ) || ( comp_msg -> slurm_rc == ESLURMD_UID_NOT_FOUND ) || ( comp_msg -> slurm_rc == ESLURMD_GID_NOT_FOUND ) || ( comp_msg -> slurm_rc == ESLURMD_INVALID_ACCT_FREQ ) ) {
 error ( "Slurmd error running JobId=%u on %s=%s: %s" , comp_msg -> job_id , msg_title , nodes , slurm_strerror ( comp_msg -> slurm_rc ) ) ;
 }
 else if ( comp_msg -> slurm_rc != SLURM_SUCCESS ) {
 error ( "slurmd error running JobId=%u on %s=%s: %s" , comp_msg -> job_id , msg_title , nodes , slurm_strerror ( comp_msg -> slurm_rc ) ) ;
 slurmctld_diag_stats . jobs_failed ++ ;
 if ( error_code == SLURM_SUCCESS ) {

 select_g_select_jobinfo_get ( job_ptr -> select_jobinfo , SELECT_JOBDATA_BLOCK_ID , & block_desc . bg_block_id ) ;
 }

 update_front_end_msg_t update_node_msg ;
 memset ( & update_node_msg , 0 , sizeof ( update_front_end_msg_t ) ) ;
 update_node_msg . name = job_ptr -> front_end_ptr -> name ;
 update_node_msg . node_state = NODE_STATE_DRAIN ;
 update_node_msg . reason = "batch job complete failure" ;
 error_code = update_front_end ( & update_node_msg ) ;
 }


 dump_job = true ;
 dump_node = true ;
 }
 }
 if ( msg -> msg_type == REQUEST_COMPLETE_BATCH_JOB ) job_epilog_complete ( comp_msg -> job_id , comp_msg -> node_name , 0 ) ;
 i = job_complete ( comp_msg -> job_id , uid , job_requeue , false , comp_msg -> job_rc ) ;
 error_code = MAX ( error_code , i ) ;
 if ( ! running_composite ) {
 unlock_slurmctld ( job_write_lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 }

 block_desc . reason = slurm_strerror ( comp_msg -> slurm_rc ) ;
 block_desc . state = BG_BLOCK_ERROR_FLAG ;
 i = select_g_update_block ( & block_desc ) ;
 error_code = MAX ( error_code , i ) ;
 xfree ( block_desc . bg_block_id ) ;
 }

 if ( ( powercap_get_cluster_current_cap ( ) != 0 ) && ( which_power_layout ( ) == 2 ) ) {
 layouts_entity_pull_kv ( "power" , "Cluster" , "CurrentSumPower" ) ;
 }
 if ( error_code ) {
 debug2 ( "_slurm_rpc_complete_batch_script JobId=%u: %s " , comp_msg -> job_id , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug2 ( "_slurm_rpc_complete_batch_script JobId=%u %s" , comp_msg -> job_id , TIME_STR ) ;
 slurmctld_diag_stats . jobs_completed ++ ;
 dump_job = true ;
 if ( replace_batch_job ( msg , job_ptr , running_composite ) ) * run_scheduler = true ;
 }
 if ( ! running_composite && * run_scheduler ) ( void ) schedule ( 0 ) ;
 if ( dump_job ) ( void ) schedule_job_save ( ) ;
 if ( dump_node ) ( void ) schedule_node_save ( ) ;
 }