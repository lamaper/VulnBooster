static int MGCPcalls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * MGCPinfo ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 voip_calls_info_t * tmp_listinfo ;
 voip_calls_info_t * callsinfo = NULL ;
 mgcp_calls_info_t * tmp_mgcpinfo = NULL ;
 GList * list ;
 GList * listGraph ;
 gchar * frame_label = NULL ;
 gchar * comment = NULL ;
 seq_analysis_item_t * gai ;
 gboolean newcall = FALSE ;
 gboolean fromEndpoint = FALSE ;
 gdouble diff_time ;
 const mgcp_info_t * pi = ( const mgcp_info_t * ) MGCPinfo ;
 if ( ( pi -> mgcp_type == MGCP_REQUEST ) && ! pi -> is_duplicate ) {
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( ( tmp_listinfo -> protocol == VOIP_MGCP ) && ( tmp_listinfo -> call_active_state == VOIP_ACTIVE ) ) {
 tmp_mgcpinfo = ( mgcp_calls_info_t * ) tmp_listinfo -> prot_info ;
 if ( pi -> endpointId != NULL ) {
 if ( g_ascii_strcasecmp ( tmp_mgcpinfo -> endpointId , pi -> endpointId ) == 0 ) {
 diff_time = nstime_to_sec ( & pinfo -> rel_ts ) - nstime_to_sec ( & tmp_listinfo -> stop_rel_ts ) ;
 if ( ( ( tmp_listinfo -> call_state == VOIP_CANCELLED ) || ( tmp_listinfo -> call_state == VOIP_COMPLETED ) || ( tmp_listinfo -> call_state == VOIP_REJECTED ) ) && ( diff_time > 2 ) ) {
 tmp_listinfo -> call_active_state = VOIP_INACTIVE ;
 }
 else {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 }
 }
 list = g_list_next ( list ) ;
 }
 if ( callsinfo == NULL ) {
 if ( ( strcmp ( pi -> code , "NTFY" ) == 0 ) && isSignal ( "hd" , pi -> observedEvents ) ) {
 fromEndpoint = TRUE ;
 newcall = TRUE ;
 }
 else if ( strcmp ( pi -> code , "CRCX" ) == 0 ) {
 fromEndpoint = FALSE ;
 newcall = TRUE ;
 }
 if ( ! newcall ) return 0 ;
 }
 }
 else if ( ( ( pi -> mgcp_type == MGCP_RESPONSE ) && pi -> request_available ) || ( ( pi -> mgcp_type == MGCP_REQUEST ) && pi -> is_duplicate ) ) {
 listGraph = g_list_first ( tapinfo -> graph_analysis -> list ) ;
 while ( listGraph ) {
 gai = ( seq_analysis_item_t * ) listGraph -> data ;
 if ( gai -> fd -> num == pi -> req_num ) {
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_MGCP ) {
 if ( tmp_listinfo -> call_num == gai -> conv_num ) {
 tmp_mgcpinfo = ( mgcp_calls_info_t * ) tmp_listinfo -> prot_info ;
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 if ( callsinfo != NULL ) break ;
 }
 listGraph = g_list_next ( listGraph ) ;
 }
 if ( callsinfo == NULL ) return 0 ;
 }
 else return 0 ;
 if ( callsinfo == NULL ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_CALL_SETUP ;
 if ( fromEndpoint ) {
 callsinfo -> from_identity = g_strdup ( pi -> endpointId ) ;
 callsinfo -> to_identity = g_strdup ( "" ) ;
 }
 else {
 callsinfo -> from_identity = g_strdup ( "" ) ;
 callsinfo -> to_identity = g_strdup ( pi -> endpointId ) ;
 }
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , & ( pinfo -> src ) ) ;
 callsinfo -> selected = FALSE ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> protocol = VOIP_MGCP ;
 callsinfo -> prot_info = g_malloc ( sizeof ( mgcp_calls_info_t ) ) ;
 callsinfo -> free_prot_info = g_free ;
 tmp_mgcpinfo = ( mgcp_calls_info_t * ) callsinfo -> prot_info ;
 tmp_mgcpinfo -> endpointId = g_strdup ( pi -> endpointId ) ;
 tmp_mgcpinfo -> fromEndpoint = fromEndpoint ;
 callsinfo -> npackets = 0 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 g_assert ( tmp_mgcpinfo != NULL ) ;
 switch ( pi -> mgcp_type ) {
 case MGCP_REQUEST : if ( ( strcmp ( pi -> code , "NTFY" ) == 0 ) && ( pi -> observedEvents != NULL ) ) {
 frame_label = g_strdup_printf ( "%s ObsEvt:%s" , pi -> code , pi -> observedEvents ) ;
 if ( tmp_mgcpinfo -> fromEndpoint ) {
 if ( callsinfo -> to_identity [ 0 ] == '\0' ) mgcpDialedDigits ( pi -> observedEvents , & ( callsinfo -> to_identity ) ) ;
 }
 else if ( isSignal ( "hd" , pi -> observedEvents ) ) callsinfo -> call_state = VOIP_IN_CALL ;
 if ( isSignal ( "hu" , pi -> observedEvents ) ) {
 if ( ( callsinfo -> call_state == VOIP_CALL_SETUP ) || ( callsinfo -> call_state == VOIP_RINGING ) ) {
 callsinfo -> call_state = VOIP_CANCELLED ;
 }
 else {
 callsinfo -> call_state = VOIP_COMPLETED ;
 }
 }
 }
 else if ( strcmp ( pi -> code , "RQNT" ) == 0 ) {
 if ( tmp_mgcpinfo -> fromEndpoint && isSignal ( "" , pi -> signalReq ) && ( callsinfo -> call_state == VOIP_RINGING ) ) {
 callsinfo -> call_state = VOIP_IN_CALL ;
 }
 if ( isSignal ( "rg" , pi -> signalReq ) || isSignal ( "rt" , pi -> signalReq ) ) {
 callsinfo -> call_state = VOIP_RINGING ;
 }
 if ( ( isSignal ( "ro" , pi -> signalReq ) || isSignal ( "bz" , pi -> signalReq ) ) && ( ( callsinfo -> call_state == VOIP_CALL_SETUP ) || ( callsinfo -> call_state == VOIP_RINGING ) ) ) {
 callsinfo -> call_state = VOIP_REJECTED ;
 }
 if ( pi -> signalReq != NULL ) frame_label = g_strdup_printf ( "%s%sSigReq:%s" , pi -> code , ( pi -> hasDigitMap == TRUE ) ? " DigitMap " : "" , pi -> signalReq ) ;
 else frame_label = g_strdup_printf ( "%s%s" , pi -> code , ( pi -> hasDigitMap == TRUE ) ? " DigitMap " : "" ) ;
 if ( ! tmp_mgcpinfo -> fromEndpoint ) mgcpCallerID ( pi -> signalReq , & ( callsinfo -> from_identity ) ) ;
 }
 else if ( strcmp ( pi -> code , "DLCX" ) == 0 ) {
 if ( ! tmp_mgcpinfo -> fromEndpoint ) {
 if ( ( callsinfo -> call_state == VOIP_CALL_SETUP ) || ( callsinfo -> call_state == VOIP_RINGING ) ) {
 callsinfo -> call_state = VOIP_CANCELLED ;
 }
 }
 }
 if ( frame_label == NULL ) frame_label = g_strdup ( pi -> code ) ;
 break ;
 case MGCP_RESPONSE : frame_label = g_strdup_printf ( "%u (%s)" , pi -> rspcode , pi -> code ) ;
 break ;
 case MGCP_OTHERS : break ;
 }
 comment = g_strdup_printf ( "MGCP %s %s%s" , tmp_mgcpinfo -> endpointId , ( pi -> mgcp_type == MGCP_REQUEST ) ? "Request" : "Response" , pi -> is_duplicate ? " Duplicate" : "" ) ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 g_free ( comment ) ;
 g_free ( frame_label ) ;
 if ( ( sdp_summary != NULL ) && ( sdp_frame_num == pinfo -> fd -> num ) ) {
 append_to_frame_graph ( tapinfo , pinfo -> fd -> num , sdp_summary , NULL ) ;
 g_free ( sdp_summary ) ;
 sdp_summary = NULL ;
 }
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }