static void RTP_packet_draw ( void * prs _U_ ) {
 voip_rtp_tapinfo_t * rtp_tapinfo = & the_tapinfo_rtp_struct ;
 GList * rtp_streams_list ;
 voip_rtp_stream_info_t * rtp_listinfo ;
 seq_analysis_item_t * gai ;
 seq_analysis_item_t * new_gai ;
 guint16 conv_num ;
 guint32 duration ;
 gchar time_str [ COL_MAX_LEN ] ;
 rtp_streams_list = g_list_first ( rtp_tapinfo -> list ) ;
 while ( rtp_streams_list ) {
 rtp_listinfo = ( voip_rtp_stream_info_t * ) rtp_streams_list -> data ;
 gai = ( seq_analysis_item_t * ) g_hash_table_lookup ( the_tapinfo_struct . graph_analysis -> ht , & rtp_listinfo -> setup_frame_number ) ;
 if ( gai != NULL ) {
 conv_num = gai -> conv_num ;
 gai = ( seq_analysis_item_t * ) g_hash_table_lookup ( the_tapinfo_struct . graph_analysis -> ht , & rtp_listinfo -> start_fd -> num ) ;
 if ( gai != NULL ) {
 duration = ( guint32 ) ( nstime_to_msec ( & rtp_listinfo -> stop_rel_ts ) - nstime_to_msec ( & rtp_listinfo -> start_rel_ts ) ) ;
 g_free ( gai -> comment ) ;
 gai -> comment = g_strdup_printf ( "%s Num packets:%u Duration:%u.%03us SSRC:0x%X" , ( rtp_listinfo -> is_srtp ) ? "SRTP" : "RTP" , rtp_listinfo -> npackets , duration / 1000 , ( duration % 1000 ) , rtp_listinfo -> ssrc ) ;
 }
 else {
 new_gai = ( seq_analysis_item_t * ) g_malloc ( sizeof ( seq_analysis_item_t ) ) ;
 new_gai -> fd = rtp_listinfo -> start_fd ;
 COPY_ADDRESS ( & ( new_gai -> src_addr ) , & ( rtp_listinfo -> src_addr ) ) ;
 COPY_ADDRESS ( & ( new_gai -> dst_addr ) , & ( rtp_listinfo -> dest_addr ) ) ;
 new_gai -> port_src = rtp_listinfo -> src_port ;
 new_gai -> port_dst = rtp_listinfo -> dest_port ;
 duration = ( guint32 ) ( nstime_to_msec ( & rtp_listinfo -> stop_rel_ts ) - nstime_to_msec ( & rtp_listinfo -> start_rel_ts ) ) ;
 new_gai -> frame_label = g_strdup_printf ( "%s (%s) %s" , ( rtp_listinfo -> is_srtp ) ? "SRTP" : "RTP" , rtp_listinfo -> pt_str , ( rtp_listinfo -> rtp_event == - 1 ) ? "" : val_to_str_ext_const ( rtp_listinfo -> rtp_event , & rtp_event_type_values_ext , "Unknown RTP Event" ) ) ;
 new_gai -> comment = g_strdup_printf ( "%s Num packets:%u Duration:%u.%03us SSRC:0x%X" , ( rtp_listinfo -> is_srtp ) ? "SRTP" : "RTP" , rtp_listinfo -> npackets , duration / 1000 , ( duration % 1000 ) , rtp_listinfo -> ssrc ) ;
 new_gai -> conv_num = conv_num ;
 set_fd_time ( cfile . epan , new_gai -> fd , time_str ) ;
 new_gai -> time_str = g_strdup ( time_str ) ;
 new_gai -> display = FALSE ;
 new_gai -> line_style = 2 ;
 the_tapinfo_struct . graph_analysis -> list = g_list_prepend ( the_tapinfo_struct . graph_analysis -> list , new_gai ) ;
 g_hash_table_insert ( the_tapinfo_struct . graph_analysis -> ht , & rtp_listinfo -> start_fd , new_gai ) ;
 }
 }
 rtp_streams_list = g_list_next ( rtp_streams_list ) ;
 }
 }