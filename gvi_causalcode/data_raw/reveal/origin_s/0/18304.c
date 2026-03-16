static void _kill_job_on_msg_fail ( uint32_t job_id ) {
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , READ_LOCK }
 ;
 error ( "Job allocate response msg send failure, killing JobId=%u" , job_id ) ;
 lock_slurmctld ( job_write_lock ) ;
 job_complete ( job_id , slurmctld_conf . slurm_user_id , false , false , SIGTERM ) ;
 unlock_slurmctld ( job_write_lock ) ;
 }