extern int slurm_fail_job ( uint32_t job_id , uint32_t job_state ) {
 int error_code ;
 DEF_TIMERS ;
 slurmctld_lock_t job_write_lock = {
 NO_LOCK , WRITE_LOCK , WRITE_LOCK , NO_LOCK , NO_LOCK }
 ;
 START_TIMER ;
 lock_slurmctld ( job_write_lock ) ;
 error_code = job_fail ( job_id , job_state ) ;
 unlock_slurmctld ( job_write_lock ) ;
 END_TIMER2 ( "slurm_fail_job" ) ;
 return error_code ;
 }