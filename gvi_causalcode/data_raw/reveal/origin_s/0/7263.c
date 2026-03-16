static k12_t * new_k12_file_data ( void ) {
 k12_t * fd = g_new ( k12_t , 1 ) ;
 fd -> file_len = 0 ;
 fd -> num_of_records = 0 ;
 fd -> src_by_name = g_hash_table_new ( g_str_hash , g_str_equal ) ;
 fd -> src_by_id = g_hash_table_new ( g_direct_hash , g_direct_equal ) ;
 fd -> seq_read_buff = NULL ;
 fd -> seq_read_buff_len = 0 ;
 fd -> rand_read_buff = NULL ;
 fd -> rand_read_buff_len = 0 ;
 ws_buffer_init ( & ( fd -> extra_info ) , 100 ) ;
 return fd ;
 }