static int VoIPcalls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * VoIPinfo ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 voip_calls_info_t * callsinfo = NULL ;
 voip_calls_info_t * tmp_listinfo ;
 GList * list = NULL ;
 const voip_packet_info_t * pi = ( const voip_packet_info_t * ) VoIPinfo ;
 if ( pi -> call_id ) list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_COMMON ) {
 if ( ! strcmp ( pi -> call_id , tmp_listinfo -> call_id ) ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 if ( callsinfo == NULL ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_active_state = pi -> call_active_state ;
 callsinfo -> call_state = pi -> call_state ;
 callsinfo -> call_id = g_strdup ( ( pi -> call_id ) ? pi -> call_id : "" ) ;
 callsinfo -> from_identity = g_strdup ( ( pi -> from_identity ) ? pi -> from_identity : "" ) ;
 callsinfo -> to_identity = g_strdup ( ( pi -> to_identity ) ? pi -> to_identity : "" ) ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , & ( pinfo -> src ) ) ;
 callsinfo -> selected = FALSE ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> protocol = VOIP_COMMON ;
 callsinfo -> protocol_name = g_strdup ( ( pi -> protocol_name ) ? pi -> protocol_name : "" ) ;
 callsinfo -> call_comment = g_strdup ( ( pi -> call_comment ) ? pi -> call_comment : "" ) ;
 callsinfo -> prot_info = NULL ;
 callsinfo -> free_prot_info = NULL ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 callsinfo -> npackets = 0 ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 callsinfo -> call_active_state = pi -> call_active_state ;
 if ( ( callsinfo -> call_state != VOIP_COMPLETED ) && ( pi -> call_state == VOIP_COMPLETED ) ) tapinfo -> completed_calls ++ ;
 if ( pi -> call_state != VOIP_NO_STATE ) callsinfo -> call_state = pi -> call_state ;
 if ( pi -> call_comment ) {
 g_free ( callsinfo -> call_comment ) ;
 callsinfo -> call_comment = g_strdup ( pi -> call_comment ) ;
 }
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 add_to_graph ( tapinfo , pinfo , ( pi -> frame_label ) ? pi -> frame_label : "VoIP msg" , pi -> frame_comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }