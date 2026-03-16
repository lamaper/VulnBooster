static void _slurmctld_free_comp_msg_list ( void * x ) {
 slurm_msg_t * msg = ( slurm_msg_t * ) x ;
 if ( msg ) {
 if ( msg -> msg_type == REQUEST_BATCH_JOB_LAUNCH ) {
 slurm_free_job_launch_msg ( msg -> data ) ;
 msg -> data = NULL ;
 }
 slurm_free_comp_msg_list ( msg ) ;
 }
 }