static void insert_to_graph_t38 ( voip_calls_tapinfo_t * tapinfo _U_ , packet_info * pinfo , const gchar * frame_label , const gchar * comment , guint16 call_num , address * src_addr , address * dst_addr , guint16 line_style , guint32 frame_num ) {
 seq_analysis_item_t * gai , * new_gai ;
 GList * list ;
 guint item_num ;
 gboolean inserted ;
 gchar time_str [ COL_MAX_LEN ] ;
 new_gai = ( seq_analysis_item_t * ) g_malloc ( sizeof ( seq_analysis_item_t ) ) ;
 new_gai -> fd = packet_list_get_row_data ( frame_num ) ;
 COPY_ADDRESS ( & ( new_gai -> src_addr ) , src_addr ) ;
 COPY_ADDRESS ( & ( new_gai -> dst_addr ) , dst_addr ) ;
 new_gai -> port_src = pinfo -> srcport ;
 new_gai -> port_dst = pinfo -> destport ;
 if ( frame_label != NULL ) new_gai -> frame_label = g_strdup ( frame_label ) ;
 else new_gai -> frame_label = g_strdup ( "" ) ;
 if ( comment != NULL ) new_gai -> comment = g_strdup ( comment ) ;
 else new_gai -> comment = g_strdup ( "" ) ;
 new_gai -> conv_num = call_num ;
 new_gai -> line_style = line_style ;
 set_fd_time ( cfile . epan , new_gai -> fd , time_str ) ;
 new_gai -> time_str = g_strdup ( time_str ) ;
 new_gai -> display = FALSE ;
 item_num = 0 ;
 inserted = FALSE ;
 list = g_list_first ( tapinfo -> graph_analysis -> list ) ;
 while ( list ) {
 gai = ( seq_analysis_item_t * ) list -> data ;
 if ( gai -> fd -> num > frame_num ) {
 the_tapinfo_struct . graph_analysis -> list = g_list_insert ( the_tapinfo_struct . graph_analysis -> list , new_gai , item_num ) ;
 g_hash_table_insert ( tapinfo -> graph_analysis -> ht , & new_gai -> fd -> num , new_gai ) ;
 inserted = TRUE ;
 break ;
 }
 list = g_list_next ( list ) ;
 item_num ++ ;
 }
 if ( ! inserted ) {
 tapinfo -> graph_analysis -> list = g_list_prepend ( tapinfo -> graph_analysis -> list , new_gai ) ;
 g_hash_table_insert ( tapinfo -> graph_analysis -> ht , & new_gai -> fd -> num , new_gai ) ;
 }
 }