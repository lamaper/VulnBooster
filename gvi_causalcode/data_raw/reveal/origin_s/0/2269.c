void voip_calls_reset ( voip_calls_tapinfo_t * tapinfo ) {
 voip_calls_info_t * callsinfo ;
 voip_rtp_tapinfo_t * rtp_tapinfo = & the_tapinfo_rtp_struct ;
 voip_rtp_stream_info_t * strinfo ;
 seq_analysis_item_t * graph_item ;
 GList * list ;


 while ( list ) {
 callsinfo = ( voip_calls_info_t * ) list -> data ;
 g_free ( callsinfo -> call_id ) ;
 g_free ( callsinfo -> from_identity ) ;
 g_free ( callsinfo -> to_identity ) ;
 g_free ( ( void * ) ( callsinfo -> initial_speaker . data ) ) ;
 g_free ( callsinfo -> protocol_name ) ;
 g_free ( callsinfo -> call_comment ) ;
 if ( callsinfo -> free_prot_info && callsinfo -> prot_info ) callsinfo -> free_prot_info ( callsinfo -> prot_info ) ;
 g_free ( list -> data ) ;
 list = g_list_next ( list ) ;
 }
 g_list_free ( tapinfo -> callsinfo_list ) ;
 if ( NULL != tapinfo -> callsinfo_hashtable [ SIP_HASH ] ) g_hash_table_remove_all ( tapinfo -> callsinfo_hashtable [ SIP_HASH ] ) ;
 tapinfo -> callsinfo_list = NULL ;
 tapinfo -> ncalls = 0 ;
 tapinfo -> npackets = 0 ;
 tapinfo -> start_packets = 0 ;
 tapinfo -> completed_calls = 0 ;
 tapinfo -> rejected_calls = 0 ;
 tapinfo -> reversed = 0 ;
 if ( NULL != tapinfo -> graph_analysis -> ht ) g_hash_table_remove_all ( tapinfo -> graph_analysis -> ht ) ;
 list = g_list_first ( tapinfo -> graph_analysis -> list ) ;
 while ( list ) {
 graph_item = ( seq_analysis_item_t * ) list -> data ;
 g_free ( graph_item -> frame_label ) ;
 g_free ( graph_item -> comment ) ;
 g_free ( ( void * ) graph_item -> src_addr . data ) ;
 g_free ( ( void * ) graph_item -> dst_addr . data ) ;
 g_free ( graph_item -> time_str ) ;
 g_free ( list -> data ) ;
 list = g_list_next ( list ) ;
 }
 g_list_free ( tapinfo -> graph_analysis -> list ) ;
 tapinfo -> graph_analysis -> nconv = 0 ;
 tapinfo -> graph_analysis -> list = NULL ;
 ++ ( tapinfo -> launch_count ) ;
 list = g_list_first ( rtp_tapinfo -> list ) ;
 while ( list ) {
 strinfo = ( voip_rtp_stream_info_t * ) list -> data ;
 g_free ( strinfo -> pt_str ) ;
 list = g_list_next ( list ) ;
 }
 g_list_free ( rtp_tapinfo -> list ) ;
 rtp_tapinfo -> list = NULL ;
 return ;
 }