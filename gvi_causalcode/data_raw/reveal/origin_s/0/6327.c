static int diameterstat_packet ( void * pss , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * prv ) {
 guint i = 0 ;
 srt_stat_table * diameter_srt_table ;
 srt_data_t * data = ( srt_data_t * ) pss ;
 const diameter_req_ans_pair_t * diameter = ( const diameter_req_ans_pair_t * ) prv ;
 int * idx = NULL ;
 if ( ! diameter || diameter -> processing_request || ! diameter -> req_frame ) return 0 ;
 diameter_srt_table = g_array_index ( data -> srt_array , srt_stat_table * , i ) ;
 idx = ( int * ) g_hash_table_lookup ( diameterstat_cmd_str_hash , diameter -> cmd_str ) ;
 if ( idx == NULL ) {
 idx = ( int * ) g_malloc ( sizeof ( int ) ) ;
 * idx = ( int ) g_hash_table_size ( diameterstat_cmd_str_hash ) ;
 g_hash_table_insert ( diameterstat_cmd_str_hash , ( gchar * ) diameter -> cmd_str , idx ) ;
 init_srt_table_row ( diameter_srt_table , * idx , ( const char * ) diameter -> cmd_str ) ;
 }
 add_srt_table_data ( diameter_srt_table , * idx , & diameter -> req_time , pinfo ) ;
 return 1 ;
 }