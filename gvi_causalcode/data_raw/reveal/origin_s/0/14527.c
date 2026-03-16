inline static void _slurm_rpc_checkpoint_comp ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 checkpoint_comp_msg_t * ckpt_ptr = ( checkpoint_comp_msg_t * ) msg -> data ;
 slurmctld_lock_t job_read_lock = {
 NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_CHECKPOINT_COMP from uid=%d" , uid ) ;
 lock_slurmctld ( job_read_lock ) ;
 error_code = job_step_checkpoint_comp ( ckpt_ptr , uid , msg -> conn_fd , msg -> protocol_version ) ;
 unlock_slurmctld ( job_read_lock ) ;
 END_TIMER2 ( "_slurm_rpc_checkpoint_comp" ) ;
 if ( error_code ) {
 info ( "_slurm_rpc_checkpoint_comp %u.%u: %s" , ckpt_ptr -> job_id , ckpt_ptr -> step_id , slurm_strerror ( error_code ) ) ;
 }
 else {
 info ( "_slurm_rpc_checkpoint_comp %u.%u %s" , ckpt_ptr -> job_id , ckpt_ptr -> step_id , TIME_STR ) ;
 }
 }