static int T38_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * T38info ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 voip_calls_info_t * callsinfo = NULL ;
 voip_calls_info_t * tmp_listinfo ;
 GList * voip_calls_graph_list ;
 GList * list ;
 gchar * frame_label = NULL ;
 gchar * comment = NULL ;
 seq_analysis_item_t * tmp_gai , * gai = NULL ;
 guint16 line_style = 2 ;
 double duration ;
 int conv_num = - 1 ;
 const t38_packet_info * pi = ( const t38_packet_info * ) T38info ;
 if ( pi -> setup_frame_number != 0 ) {
 voip_calls_graph_list = g_list_first ( tapinfo -> graph_analysis -> list ) ;
 while ( voip_calls_graph_list ) {
 tmp_gai = ( seq_analysis_item_t * ) voip_calls_graph_list -> data ;
 if ( pi -> setup_frame_number == tmp_gai -> fd -> num ) {
 gai = tmp_gai ;
 break ;
 }
 voip_calls_graph_list = g_list_next ( voip_calls_graph_list ) ;
 }
 if ( gai ) conv_num = ( int ) gai -> conv_num ;
 }
 if ( ( pi -> setup_frame_number == 0 ) || ( gai == NULL ) ) {
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == MEDIA_T38 ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 list = g_list_next ( list ) ;
 }
 if ( callsinfo == NULL ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_UNKNOWN ;
 callsinfo -> from_identity = g_strdup ( "T38 Media only" ) ;
 callsinfo -> to_identity = g_strdup ( "T38 Media only" ) ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , & ( pinfo -> src ) ) ;
 callsinfo -> selected = FALSE ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> protocol = MEDIA_T38 ;
 callsinfo -> prot_info = NULL ;
 callsinfo -> free_prot_info = NULL ;
 callsinfo -> npackets = 0 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 conv_num = ( int ) callsinfo -> call_num ;
 }
 if ( conv_num == - 1 ) {
 return 0 ;
 }
 if ( pi -> type_msg == 0 ) {
 frame_label = g_strdup ( val_to_str ( pi -> t30ind_value , t38_T30_indicator_vals , "Ukn (0x%02X)" ) ) ;
 comment = g_strdup_printf ( "t38:t30 Ind:%s" , val_to_str ( pi -> t30ind_value , t38_T30_indicator_vals , "Ukn (0x%02X)" ) ) ;
 line_style = 1 ;
 }
 else if ( pi -> type_msg == 1 ) {
 switch ( pi -> Data_Field_field_type_value ) {
 case 0 : break ;
 case 2 : case 4 : frame_label = g_strdup_printf ( "%s %s" , val_to_str_ext ( pi -> t30_Facsimile_Control & 0x7F , & t30_facsimile_control_field_vals_short_ext , "Ukn (0x%02X)" ) , pi -> desc ) ;
 comment = g_strdup_printf ( "t38:%s:HDLC:%s" , val_to_str ( pi -> data_value , t38_T30_data_vals , "Ukn (0x%02X)" ) , val_to_str_ext ( pi -> t30_Facsimile_Control & 0x7F , & t30_facsimile_control_field_vals_ext , "Ukn (0x%02X)" ) ) ;
 break ;
 case 3 : case 5 : frame_label = g_strdup ( pi -> Data_Field_field_type_value == 3 ? "fcs-BAD" : "fcs-BAD-sig-end" ) ;
 comment = g_strdup_printf ( "WARNING: received t38:%s:HDLC:%s" , val_to_str ( pi -> data_value , t38_T30_data_vals , "Ukn (0x%02X)" ) , pi -> Data_Field_field_type_value == 3 ? "fcs-BAD" : "fcs-BAD-sig-end" ) ;
 break ;
 case 7 : duration = nstime_to_sec ( & pinfo -> rel_ts ) - pi -> time_first_t4_data ;
 frame_label = g_strdup_printf ( "t4-non-ecm-data:%s" , val_to_str ( pi -> data_value , t38_T30_data_vals , "Ukn (0x%02X)" ) ) ;
 comment = g_strdup_printf ( "t38:t4-non-ecm-data:%s Duration: %.2fs %s" , val_to_str ( pi -> data_value , t38_T30_data_vals , "Ukn (0x%02X)" ) , duration , pi -> desc_comment ) ;
 insert_to_graph_t38 ( tapinfo , pinfo , frame_label , comment , ( guint16 ) conv_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , line_style , pi -> frame_num_first_t4_data ) ;
 break ;
 }
 }
 if ( frame_label && ! ( pi -> Data_Field_field_type_value == 7 && pi -> type_msg == 1 ) ) {
 add_to_graph ( tapinfo , pinfo , frame_label , comment , ( guint16 ) conv_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , line_style ) ;
 }
 g_free ( comment ) ;
 g_free ( frame_label ) ;
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }