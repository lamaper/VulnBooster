static void _slurm_rpc_step_update ( slurm_msg_t * msg ) {
 DEF_TIMERS ;
 step_update_request_msg_t * req = ( step_update_request_msg_t * ) msg -> data ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 int rc ;
 START_TIMER ;
 if ( slurmctld_conf . debug_flags & DEBUG_FLAG_STEPS ) info ( "Processing RPC: REQUEST_STEP_UPDATE, from uid=%d" , uid ) ;
 lock_slurmctld ( job_write_lock ) ;
 rc = update_step ( req , uid ) ;
 unlock_slurmctld ( job_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_step_update" ) ;
 slurm_send_rc_msg ( msg , rc ) ;
 }