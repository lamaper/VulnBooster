static void diameterstat_init ( struct register_srt * srt _U_ , GArray * srt_array , srt_gui_init_cb gui_callback , void * gui_data ) {
 srt_stat_table * diameter_srt_table ;
 int * idx ;
 if ( diameterstat_cmd_str_hash != NULL ) {
 g_hash_table_destroy ( diameterstat_cmd_str_hash ) ;
 }
 idx = ( int * ) g_malloc ( sizeof ( int ) ) ;
 * idx = 0 ;
 diameterstat_cmd_str_hash = g_hash_table_new ( g_str_hash , g_str_equal ) ;
 g_hash_table_insert ( diameterstat_cmd_str_hash , ( gchar * ) "Unknown" , idx ) ;
 diameter_srt_table = init_srt_table ( "Diameter Requests" , NULL , srt_array , DIAMETER_NUM_PROCEDURES , NULL , NULL , gui_callback , gui_data , NULL ) ;
 init_srt_table_row ( diameter_srt_table , 0 , "Unknown" ) ;
 }