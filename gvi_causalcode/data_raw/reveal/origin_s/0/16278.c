static void iax_cleanup_protocol ( void ) {
 g_hash_table_destroy ( iax_circuit_hashtab ) ;
 g_hash_table_destroy ( iax_fid_table ) ;
 reassembly_table_destroy ( & iax_reassembly_table ) ;
 }