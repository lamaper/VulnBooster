static void destroy_k12_file_data ( k12_t * fd ) {
 g_hash_table_destroy ( fd -> src_by_id ) ;
 g_hash_table_foreach_remove ( fd -> src_by_name , destroy_srcdsc , NULL ) ;
 g_hash_table_destroy ( fd -> src_by_name ) ;
 ws_buffer_free ( & ( fd -> extra_info ) ) ;
 g_free ( fd -> seq_read_buff ) ;
 g_free ( fd -> rand_read_buff ) ;
 g_free ( fd ) ;
 }