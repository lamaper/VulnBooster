extern void free_rpc_stats ( void ) {
 slurm_mutex_lock ( & rpc_mutex ) ;
 xfree ( rpc_type_cnt ) ;
 xfree ( rpc_type_id ) ;
 xfree ( rpc_type_time ) ;
 rpc_type_size = 0 ;
 xfree ( rpc_user_cnt ) ;
 xfree ( rpc_user_id ) ;
 xfree ( rpc_user_time ) ;
 rpc_user_size = 0 ;
 slurm_mutex_unlock ( & rpc_mutex ) ;
 }