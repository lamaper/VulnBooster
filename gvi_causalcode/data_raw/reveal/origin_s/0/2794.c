static void iax_init_protocol ( void ) {
 iax_circuit_hashtab = g_hash_table_new ( iax_circuit_hash , iax_circuit_equal ) ;
 circuitcount = 0 ;
 iax_fid_table = g_hash_table_new ( g_direct_hash , g_direct_equal ) ;
 reassembly_table_init ( & iax_reassembly_table , & addresses_reassembly_table_functions ) ;
 }