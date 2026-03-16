inline static void _slurm_rpc_checkpoint ( slurm_msg_t * msg ) {
 int error_code = SLURM_SUCCESS ;
 DEF_TIMERS ;
 checkpoint_msg_t * ckpt_ptr = ( checkpoint_msg_t * ) msg -> data ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , READ_LOCK , NO_LOCK , READ_LOCK }
 ;
 uid_t uid = g_slurm_auth_get_uid ( msg -> auth_cred , slurmctld_config . auth_info ) ;
 char * op ;
 START_TIMER ;
 switch ( ckpt_ptr -> op ) {
 case CHECK_ABLE : op = "able" ;
 break ;
 case CHECK_CREATE : op = "create" ;
 break ;
 case CHECK_DISABLE : op = "disable" ;
 break ;
 case CHECK_ENABLE : op = "enable" ;
 break ;
 case CHECK_ERROR : op = "error" ;
 break ;
 case CHECK_REQUEUE : op = "requeue" ;
 break ;
 case CHECK_RESTART : op = "restart" ;
 break ;
 case CHECK_VACATE : op = "vacate" ;
 break ;
 default : op = "unknown" ;
 }
 debug2 ( "Processing RPC: REQUEST_CHECKPOINT(%s) from uid=%u" , op , ( unsigned int ) uid ) ;
 lock_slurmctld ( job_write_lock ) ;
 if ( ckpt_ptr -> op == CHECK_RESTART ) {
 error_code = job_restart ( ckpt_ptr , uid , msg -> conn_fd , msg -> protocol_version ) ;
 }
 else if ( ckpt_ptr -> step_id == SLURM_BATCH_SCRIPT ) {
 error_code = job_checkpoint ( ckpt_ptr , uid , msg -> conn_fd , msg -> protocol_version ) ;
 }
 else {
 error_code = job_step_checkpoint ( ckpt_ptr , uid , msg -> conn_fd , msg -> protocol_version ) ;
 }
 unlock_slurmctld ( job_write_lock ) ;
 END_TIMER2 ( "_slurm_rpc_checkpoint" ) ;
 if ( error_code ) {
 if ( ckpt_ptr -> step_id == SLURM_BATCH_SCRIPT ) {
 info ( "_slurm_rpc_checkpoint %s %u: %s" , op , ckpt_ptr -> job_id , slurm_strerror ( error_code ) ) ;
 }
 else {
 info ( "_slurm_rpc_checkpoint %s %u.%u: %s" , op , ckpt_ptr -> job_id , ckpt_ptr -> step_id , slurm_strerror ( error_code ) ) ;
 }
 }
 else {
 if ( ckpt_ptr -> step_id == SLURM_BATCH_SCRIPT ) {
 info ( "_slurm_rpc_checkpoint %s for %u %s" , op , ckpt_ptr -> job_id , TIME_STR ) ;
 }
 else {
 info ( "_slurm_rpc_checkpoint %s for %u.%u %s" , op , ckpt_ptr -> job_id , ckpt_ptr -> step_id , TIME_STR ) ;
 }
 if ( ( ckpt_ptr -> op != CHECK_ABLE ) && ( ckpt_ptr -> op != CHECK_ERROR ) ) {
 schedule_job_save ( ) ;
 }
 }
 }