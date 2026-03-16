static int ACTRACEcalls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * ACTRACEinfo ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 const actrace_info_t * pi = ( const actrace_info_t * ) ACTRACEinfo ;
 GList * list ;
 actrace_cas_calls_info_t * tmp_actrace_cas_info ;
 voip_calls_info_t * tmp_listinfo ;
 voip_calls_info_t * callsinfo = NULL ;
 actrace_frame_num = pinfo -> fd -> num ;
 actrace_trunk = pi -> trunk ;
 actrace_direction = pi -> direction ;
 if ( pi -> type == 1 ) {
 address pstn_add ;
 gchar * comment = NULL ;
 callsinfo = NULL ;
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_AC_CAS ) {
 tmp_actrace_cas_info = ( actrace_cas_calls_info_t * ) tmp_listinfo -> prot_info ;
 if ( ( tmp_actrace_cas_info -> bchannel == pi -> cas_bchannel ) && ( tmp_actrace_cas_info -> trunk == actrace_trunk ) ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 SET_ADDRESS ( & pstn_add , AT_STRINGZ , 5 , "PSTN" ) ;
 if ( ! callsinfo ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_CALL_SETUP ;
 callsinfo -> from_identity = g_strdup ( "N/A" ) ;
 callsinfo -> to_identity = g_strdup ( "N/A" ) ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , actrace_direction ? & pstn_add : & ( pinfo -> src ) ) ;
 callsinfo -> selected = FALSE ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> protocol = VOIP_AC_CAS ;
 callsinfo -> prot_info = g_malloc ( sizeof ( actrace_cas_calls_info_t ) ) ;
 callsinfo -> free_prot_info = g_free ;
 tmp_actrace_cas_info = ( actrace_cas_calls_info_t * ) callsinfo -> prot_info ;
 tmp_actrace_cas_info -> bchannel = pi -> cas_bchannel ;
 tmp_actrace_cas_info -> trunk = actrace_trunk ;
 callsinfo -> npackets = 0 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 comment = g_strdup_printf ( "AC_CAS trunk:%u" , actrace_trunk ) ;
 add_to_graph ( tapinfo , pinfo , pi -> cas_frame_label , comment , callsinfo -> call_num , actrace_direction ? & pstn_add : & ( pinfo -> src ) , actrace_direction ? & ( pinfo -> src ) : & pstn_add , 1 ) ;
 g_free ( comment ) ;
 }
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }