static void add_to_graph ( voip_calls_tapinfo_t * tapinfo _U_ , packet_info * pinfo , const gchar * frame_label , const gchar * comment , guint16 call_num , address * src_addr , address * dst_addr , guint16 line_style ) {
 seq_analysis_item_t * gai ;
 gchar time_str [ COL_MAX_LEN ] ;
 gai = ( seq_analysis_item_t * ) g_malloc ( sizeof ( seq_analysis_item_t ) ) ;
 gai -> fd = pinfo -> fd ;
 COPY_ADDRESS ( & ( gai -> src_addr ) , src_addr ) ;
 COPY_ADDRESS ( & ( gai -> dst_addr ) , dst_addr ) ;
 gai -> port_src = pinfo -> srcport ;
 gai -> port_dst = pinfo -> destport ;
 if ( frame_label != NULL ) gai -> frame_label = g_strdup ( frame_label ) ;
 else gai -> frame_label = g_strdup ( "" ) ;
 if ( comment != NULL ) gai -> comment = g_strdup ( comment ) ;
 else gai -> comment = g_strdup ( "" ) ;
 gai -> conv_num = call_num ;
 gai -> line_style = line_style ;
 set_fd_time ( cfile . epan , gai -> fd , time_str ) ;
 gai -> time_str = g_strdup ( time_str ) ;
 gai -> display = FALSE ;
 tapinfo -> graph_analysis -> list = g_list_prepend ( tapinfo -> graph_analysis -> list , gai ) ;
 g_hash_table_insert ( tapinfo -> graph_analysis -> ht , & gai -> fd -> num , gai ) ;
 }