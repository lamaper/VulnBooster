void graph_analysis_data_init ( void ) {
 the_tapinfo_struct . graph_analysis = ( seq_analysis_info_t * ) g_malloc ( sizeof ( seq_analysis_info_t ) ) ;
 the_tapinfo_struct . graph_analysis -> nconv = 0 ;
 the_tapinfo_struct . graph_analysis -> list = NULL ;
 the_tapinfo_struct . graph_analysis -> ht = g_hash_table_new ( g_int_hash , g_int_equal ) ;
 }