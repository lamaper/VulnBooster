static void _throttle_fini ( int * active_rpc_cnt ) {
 slurm_mutex_lock ( & throttle_mutex ) ;
 ( * active_rpc_cnt ) -- ;
 slurm_cond_broadcast ( & throttle_cond ) ;
 slurm_mutex_unlock ( & throttle_mutex ) ;
 }