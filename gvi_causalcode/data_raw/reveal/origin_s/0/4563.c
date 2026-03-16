static void _clear_rpc_stats ( void ) {
 int i ;
 slurm_mutex_lock ( & rpc_mutex ) ;
 for ( i = 0 ;
 i < rpc_type_size ;
 i ++ ) {
 rpc_type_cnt [ i ] = 0 ;
 rpc_type_id [ i ] = 0 ;
 rpc_type_time [ i ] = 0 ;
 }
 for ( i = 0 ;
 i < rpc_user_size ;
 i ++ ) {
 rpc_user_cnt [ i ] = 0 ;
 rpc_user_id [ i ] = 0 ;
 rpc_user_time [ i ] = 0 ;
 }
 slurm_mutex_unlock ( & rpc_mutex ) ;
 }