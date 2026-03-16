static void _slurm_rpc_complete_prolog ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 complete_prolog_msg_t * comp_msg = ( complete_prolog_msg_t * ) msg -> data ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 START_TIMER ;
 debug2 ( "Processing RPC: REQUEST_COMPLETE_PROLOG from JobId=%u" , comp_msg -> job_id ) ;
 lock_slurmctld ( job_write_lock ) ;
 error_code = prolog_complete ( comp_msg -> job_id , comp_msg -> prolog_rc ) ;
 unlock_slurmctld ( job_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_complete_prolog" ) ;
 if ( error_code ) {
 info ( "_slurm_rpc_complete_prolog JobId=%u: %s " , comp_msg -> job_id , slurm_strerror ( error_code ) ) ;
 slurm_send_rc_msg ( msg , error_code ) ;
 }
 else {
 debug2 ( "_slurm_rpc_complete_prolog JobId=%u %s" , comp_msg -> job_id , TIME_STR ) ;
 slurm_send_rc_msg ( msg , SLURM_SUCCESS ) ;
 }
 }