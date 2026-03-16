static int SIPcalls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * SIPinfo ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 voip_calls_info_t * callsinfo = NULL ;
 sip_calls_info_t * tmp_sipinfo = NULL ;
 address tmp_src , tmp_dst ;
 gchar * frame_label = NULL ;
 gchar * comment = NULL ;
 gchar * key = NULL ;
 const sip_info_value_t * pi = ( const sip_info_value_t * ) SIPinfo ;
 if ( pi -> tap_call_id == NULL ) {
 return 0 ;
 }
 key = pi -> tap_call_id ;
 if ( NULL == tapinfo -> callsinfo_hashtable [ SIP_HASH ] ) {
 tapinfo -> callsinfo_hashtable [ SIP_HASH ] = g_hash_table_new_full ( g_str_hash , g_str_equal , NULL , NULL ) ;
 }
 callsinfo = ( voip_calls_info_t * ) g_hash_table_lookup ( tapinfo -> callsinfo_hashtable [ SIP_HASH ] , key ) ;
 if ( ( callsinfo == NULL ) && ( pi -> request_method != NULL ) ) {
 if ( strcmp ( pi -> request_method , "INVITE" ) == 0 ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_CALL_SETUP ;
 callsinfo -> from_identity = g_strdup ( pi -> tap_from_addr ) ;
 callsinfo -> to_identity = g_strdup ( pi -> tap_to_addr ) ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , & ( pinfo -> src ) ) ;
 callsinfo -> selected = FALSE ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> protocol = VOIP_SIP ;
 callsinfo -> prot_info = g_malloc ( sizeof ( sip_calls_info_t ) ) ;
 callsinfo -> free_prot_info = free_sip_info ;
 tmp_sipinfo = ( sip_calls_info_t * ) callsinfo -> prot_info ;
 tmp_sipinfo -> call_identifier = g_strdup ( pi -> tap_call_id ) ;
 tmp_sipinfo -> sip_state = SIP_INVITE_SENT ;
 tmp_sipinfo -> invite_cseq = pi -> tap_cseq_number ;
 callsinfo -> npackets = 0 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 g_hash_table_insert ( tapinfo -> callsinfo_hashtable [ SIP_HASH ] , tmp_sipinfo -> call_identifier , callsinfo ) ;
 }
 }
 if ( callsinfo != NULL ) {
 tmp_sipinfo = ( sip_calls_info_t * ) callsinfo -> prot_info ;
 COPY_ADDRESS ( & ( tmp_src ) , & ( pinfo -> src ) ) ;
 COPY_ADDRESS ( & ( tmp_dst ) , & ( pinfo -> dst ) ) ;
 if ( pi -> request_method == NULL ) {
 frame_label = g_strdup_printf ( "%u %s" , pi -> response_code , pi -> reason_phrase ) ;
 comment = g_strdup ( "SIP Status" ) ;
 if ( ( tmp_sipinfo && pi -> tap_cseq_number == tmp_sipinfo -> invite_cseq ) && ( ADDRESSES_EQUAL ( & tmp_dst , & ( callsinfo -> initial_speaker ) ) ) ) {
 if ( ( pi -> response_code > 199 ) && ( pi -> response_code < 300 ) && ( tmp_sipinfo -> sip_state == SIP_INVITE_SENT ) ) {
 tmp_sipinfo -> sip_state = SIP_200_REC ;
 }
 else if ( ( pi -> response_code > 299 ) && ( tmp_sipinfo -> sip_state == SIP_INVITE_SENT ) ) {
 callsinfo -> call_state = VOIP_REJECTED ;
 tapinfo -> rejected_calls ++ ;
 }
 }
 }
 else {
 frame_label = g_strdup ( pi -> request_method ) ;
 if ( ( strcmp ( pi -> request_method , "INVITE" ) == 0 ) && ( ADDRESSES_EQUAL ( & tmp_src , & ( callsinfo -> initial_speaker ) ) ) ) {
 tmp_sipinfo -> invite_cseq = pi -> tap_cseq_number ;
 callsinfo -> call_state = VOIP_CALL_SETUP ;
 comment = g_strdup_printf ( "SIP From: %s To:%s" , callsinfo -> from_identity , callsinfo -> to_identity ) ;
 }
 else if ( ( strcmp ( pi -> request_method , "ACK" ) == 0 ) && ( pi -> tap_cseq_number == tmp_sipinfo -> invite_cseq ) && ( ADDRESSES_EQUAL ( & tmp_src , & ( callsinfo -> initial_speaker ) ) ) && ( tmp_sipinfo -> sip_state == SIP_200_REC ) && ( callsinfo -> call_state == VOIP_CALL_SETUP ) ) {
 callsinfo -> call_state = VOIP_IN_CALL ;
 comment = g_strdup ( "SIP Request" ) ;
 }
 else if ( strcmp ( pi -> request_method , "BYE" ) == 0 ) {
 callsinfo -> call_state = VOIP_COMPLETED ;
 tapinfo -> completed_calls ++ ;
 comment = g_strdup ( "SIP Request" ) ;
 }
 else if ( ( strcmp ( pi -> request_method , "CANCEL" ) == 0 ) && ( pi -> tap_cseq_number == tmp_sipinfo -> invite_cseq ) && ( ADDRESSES_EQUAL ( & tmp_src , & ( callsinfo -> initial_speaker ) ) ) && ( callsinfo -> call_state == VOIP_CALL_SETUP ) ) {
 callsinfo -> call_state = VOIP_CANCELLED ;
 tmp_sipinfo -> sip_state = SIP_CANCEL_SENT ;
 comment = g_strdup ( "SIP Request" ) ;
 }
 else {
 comment = g_strdup ( "SIP Request" ) ;
 }
 }
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 g_free ( comment ) ;
 g_free ( frame_label ) ;
 g_free ( ( void * ) tmp_src . data ) ;
 g_free ( ( void * ) tmp_dst . data ) ;
 if ( ( sdp_summary != NULL ) && ( sdp_frame_num == pinfo -> fd -> num ) ) {
 append_to_frame_graph ( tapinfo , pinfo -> fd -> num , sdp_summary , NULL ) ;
 g_free ( sdp_summary ) ;
 sdp_summary = NULL ;
 }
 }
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }