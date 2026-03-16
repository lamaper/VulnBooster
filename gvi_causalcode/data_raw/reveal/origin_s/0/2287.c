static void _slurm_rpc_job_step_create ( slurm_msg_t * msg ) {
 static int active_rpc_cnt = 0 ;
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 slurm_msg_t resp ;
 struct step_record * step_rec ;
 job_step_create_response_msg_t job_step_resp ;
 job_step_create_request_msg_t * req_step_msg = ( job_step_create_request_msg_t * ) msg -> data ;
 slurm_cred_t * slurm_cred = ( slurm_cred_t * ) NULL ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , READ_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) info ( "Processing RPC: REQUEST_JOB_STEP_CREATE from uid=%d" , uid ) ;
 dump_step_desc ( req_step_msg ) ;
 if ( uid && ( uid != req_step_msg -> user_id ) ) {
 error ( "Security violation, JOB_STEP_CREATE RPC from uid=%d " "to run as uid %u" , uid , req_step_msg -> user_id ) ;
 slurm_send_rc_msg ( msg , ESLURM_USER_ID_MISSING ) ;
 return ;
 }

 info ( "Attempt to execute job step by uid=%d" , uid ) ;
 slurm_send_rc_msg ( msg , ESLURM_NO_STEPS ) ;
 return ;
 }

 slurm_send_rc_msg ( msg , EAGAIN ) ;
 return ;
 }

 lock_slurmctld ( job_write_lock ) ;
 error_code = step_create ( req_step_msg , & step_rec , false , msg -> protocol_version ) ;
 if ( error_code == SLURM_SUCCESS ) {
 error_code = _make_step_cred ( step_rec , & slurm_cred , step_rec -> start_protocol_ver ) ;
 ext_sensors_g_get_stepstartdata ( step_rec ) ;
 }
 END_TIMER2 ( "_slurm_rpc_job_step_create" ) ;
 if ( error_code ) {
 unlock_slurmctld ( job_write_lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) {
 if ( ( error_code == ESLURM_PROLOG_RUNNING ) || ( error_code == ESLURM_DISABLED ) ) {
 debug ( "%s for suspended job %u: %s" , __func__ , req_step_msg -> job_id , slurm_strerror ( error_code ) ) ;
 }
 else {
 info ( "%s for job %u: %s" , __func__ , req_step_msg -> job_id , slurm_strerror ( error_code ) ) ;
 }
 }
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 slurm_step_layout_t * layout = step_rec -> step_layout ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) info ( "sched: %s: StepId=%u.%u %s %s" , __func__ , step_rec -> job_ptr -> job_id , step_rec -> step_id , req_step_msg -> node_list , TIME_STR ) ;
 job_step_resp . job_step_id = step_rec -> step_id ;
 job_step_resp . resv_ports = step_rec -> resv_ports ;
 job_step_resp . step_layout = layout ;

 job_step_resp . step_layout -> front_end = xstrdup ( step_rec -> job_ptr -> batch_host ) ;
 }

 job_step_resp . use_protocol_ver = step_rec -> start_protocol_ver ;
 job_step_resp . select_jobinfo = step_rec -> select_jobinfo ;
 job_step_resp . switch_job = step_rec -> switch_job ;
 unlock_slurmctld ( job_write_lock ) ;
 _throttle_fini ( & active_rpc_cnt ) ;
 slurm_msg_t_init ( & resp ) ;
 resp . flags = msg -> flags ;
 resp . protocol_version = msg -> protocol_version ;
 resp . address = msg -> address ;
 resp . conn = msg -> conn ;
 resp . msg_type = RESPONSE_JOB_STEP_CREATE ;
 resp . data = & job_step_resp ;
 slurm_send_node_msg ( msg -> conn_fd , & resp ) ;
 slurm_cred_destroy ( slurm_cred ) ;
 schedule_job_save ( ) ;
 }
 }