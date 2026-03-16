extern int slurm_drain_nodes ( char * node_list , char * reason , uint32_t reason_uid ) {
 int error_code ;
 DEF_TIMERS ;
 slurmctld_lock_t node_write_lock = {
 NO_LOCK , NO_LOCK , WRITE_LOCK , NO_LOCK , NO_LOCK }
 ;
 START_TIMER ;
 lock_slurmctld ( node_write_lock ) ;
 error_code = drain_nodes ( node_list , reason , reason_uid ) ;
 unlock_slurmctld ( node_write_lock ) ;
 END_TIMER2 ( "slurm_drain_nodes" ) ;
 return error_code ;
 }