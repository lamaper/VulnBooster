static int _is_prolog_finished ( uint32_t job_id ) {
 int is_running = 0 ;
 struct job_record * job_ptr ;
 slurmctld_lock_t job_read_lock = {
 NO_LOCK , READ_LOCK , NO_LOCK , NO_LOCK , NO_LOCK }
 ;
 lock_slurmctld ( job_read_lock ) ;
 job_ptr = find_job_record ( job_id ) ;
 if ( job_ptr ) {
 is_running = ( job_ptr -> state_reason != WAIT_PROLOG ) ;
 }
 unlock_slurmctld ( job_read_lock ) ;
 return is_running ;
 }