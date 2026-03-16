static void _pack_rpc_stats ( int resp , char * * buffer_ptr , int * buffer_size , uint16_t protocol_version ) {
 uint32_t i ;
 Buf buffer ;
 slurm_mutex_lock ( & rpc_mutex ) ;
 buffer = create_buf ( * buffer_ptr , * buffer_size ) ;
 set_buf_offset ( buffer , * buffer_size ) ;
 for ( i = 0 ;
 i < rpc_type_size ;
 i ++ ) {
 if ( rpc_type_id [ i ] == 0 ) break ;
 }
 pack32 ( i , buffer ) ;
 pack16_array ( rpc_type_id , i , buffer ) ;
 pack32_array ( rpc_type_cnt , i , buffer ) ;
 pack64_array ( rpc_type_time , i , buffer ) ;
 for ( i = 1 ;
 i < rpc_user_size ;
 i ++ ) {
 if ( rpc_user_id [ i ] == 0 ) break ;
 }
 pack32 ( i , buffer ) ;
 pack32_array ( rpc_user_id , i , buffer ) ;
 pack32_array ( rpc_user_cnt , i , buffer ) ;
 pack64_array ( rpc_user_time , i , buffer ) ;
 slurm_mutex_unlock ( & rpc_mutex ) ;
 * buffer_size = get_buf_offset ( buffer ) ;
 buffer_ptr [ 0 ] = xfer_buf_data ( buffer ) ;
 }