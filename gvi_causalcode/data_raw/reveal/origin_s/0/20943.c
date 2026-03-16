static void _throttle_start ( int * active_rpc_cnt ) {
 slurm_mutex_lock ( & throttle_mutex ) ;
 while ( 1 ) {
 if ( * active_rpc_cnt == 0 ) {
 ( * active_rpc_cnt ) ++ ;
 break ;
 }


 slurm_cond_wait ( & throttle_cond , & throttle_mutex ) ;
 server_thread_incr ( ) ;

 slurm_mutex_unlock ( & throttle_mutex ) ;
 if ( LOTS_OF_AGENTS ) usleep ( 1000 ) ;
 else usleep ( 1 ) ;
 }