static int unistim_calls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * unistim_info ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 voip_calls_info_t * tmp_listinfo ;
 voip_calls_info_t * callsinfo = NULL ;
 unistim_info_t * tmp_unistim_info = NULL ;
 GList * list = NULL ;
 GString * g_tmp = NULL ;
 const gchar * frame_label = NULL ;
 gchar * comment = NULL ;
 const unistim_info_t * pi = ( const unistim_info_t * ) unistim_info ;
 g_tmp = g_string_new ( NULL ) ;
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_UNISTIM ) {
 tmp_unistim_info = ( unistim_info_t * ) tmp_listinfo -> prot_info ;
 if ( pi -> termid != 0 ) {
 if ( tmp_unistim_info -> termid == pi -> termid ) {
 if ( tmp_listinfo -> call_state == VOIP_COMPLETED || tmp_listinfo -> call_state == VOIP_UNKNOWN ) {
 }
 else {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 }
 else {
 if ( ADDRESSES_EQUAL ( & tmp_unistim_info -> it_ip , & pinfo -> dst ) && ADDRESSES_EQUAL ( & tmp_unistim_info -> ni_ip , & pinfo -> src ) && ( tmp_unistim_info -> it_port == pinfo -> destport ) ) {
 if ( tmp_listinfo -> call_state == VOIP_COMPLETED || tmp_listinfo -> call_state == VOIP_UNKNOWN ) {
 }
 else {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 else if ( ADDRESSES_EQUAL ( & tmp_unistim_info -> it_ip , & pinfo -> src ) && ADDRESSES_EQUAL ( & tmp_unistim_info -> ni_ip , & pinfo -> dst ) && ( tmp_unistim_info -> it_port == pinfo -> srcport ) ) {
 if ( tmp_listinfo -> call_state == VOIP_COMPLETED || tmp_listinfo -> call_state == VOIP_UNKNOWN ) {
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
 if ( pi -> payload_type == 2 || pi -> payload_type == 1 ) {
 if ( pi -> key_state == 1 || pi -> hook_state == 1 ) {
 if ( callsinfo == NULL ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_CALL_SETUP ;
 callsinfo -> from_identity = g_strdup_printf ( "%x" , pi -> termid ) ;
 callsinfo -> to_identity = g_strdup ( "UNKNOWN" ) ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , & ( pinfo -> src ) ) ;
 callsinfo -> selected = FALSE ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> protocol = VOIP_UNISTIM ;
 callsinfo -> prot_info = g_malloc ( sizeof ( unistim_info_t ) ) ;
 tmp_unistim_info = ( unistim_info_t * ) callsinfo -> prot_info ;
 tmp_unistim_info -> rudp_type = 0 ;
 tmp_unistim_info -> payload_type = 0 ;
 tmp_unistim_info -> sequence = pi -> sequence ;
 tmp_unistim_info -> termid = pi -> termid ;
 tmp_unistim_info -> key_val = - 1 ;
 tmp_unistim_info -> key_state = - 1 ;
 tmp_unistim_info -> hook_state = - 1 ;
 tmp_unistim_info -> stream_connect = - 1 ;
 tmp_unistim_info -> trans_connect = - 1 ;
 tmp_unistim_info -> set_termid = - 1 ;
 tmp_unistim_info -> string_data = NULL ;
 tmp_unistim_info -> key_buffer = NULL ;
 COPY_ADDRESS ( & ( tmp_unistim_info -> it_ip ) , & ( pi -> it_ip ) ) ;
 COPY_ADDRESS ( & ( tmp_unistim_info -> ni_ip ) , & ( pi -> ni_ip ) ) ;
 tmp_unistim_info -> it_port = pi -> it_port ;
 callsinfo -> free_prot_info = g_free ;
 callsinfo -> npackets = 0 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 else {
 tmp_unistim_info = ( unistim_info_t * ) callsinfo -> prot_info ;
 tmp_unistim_info -> sequence = pi -> sequence ;
 }
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 if ( pi -> key_val >= 0 && pi -> key_val <= 11 ) {
 if ( tmp_unistim_info -> key_buffer != NULL ) {
 g_string_assign ( g_tmp , tmp_unistim_info -> key_buffer ) ;
 if ( pi -> key_val == 10 ) {
 tmp_unistim_info -> key_buffer = g_strdup_printf ( "%s*" , g_tmp -> str ) ;
 }
 else if ( pi -> key_val == 11 ) {
 tmp_unistim_info -> key_buffer = g_strdup_printf ( "%s#" , g_tmp -> str ) ;
 }
 else {
 tmp_unistim_info -> key_buffer = g_strdup_printf ( "%s%d" , g_tmp -> str , pi -> key_val ) ;
 }
 }
 else {
 if ( pi -> key_val == 10 ) {
 tmp_unistim_info -> key_buffer = g_strdup ( "*" ) ;
 }
 else if ( pi -> key_val == 11 ) {
 tmp_unistim_info -> key_buffer = g_strdup ( "#" ) ;
 }
 else {
 tmp_unistim_info -> key_buffer = g_strdup_printf ( "%d" , pi -> key_val ) ;
 }
 }
 if ( pi -> key_val == 10 ) {
 comment = g_strdup_printf ( "Key Input Sent: * (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 11 ) {
 comment = g_strdup_printf ( "Key Input Sent: # (%d)" , pi -> sequence ) ;
 }
 else {
 comment = g_strdup_printf ( "Key Input Sent: %d (%d)" , pi -> key_val , pi -> sequence ) ;
 }
 }
 else if ( pi -> key_val == 12 ) {
 comment = g_strdup_printf ( "Key Input Sent: UP (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 13 ) {
 comment = g_strdup_printf ( "Key Input Sent: DOWN (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 14 ) {
 comment = g_strdup_printf ( "Key Input Sent: RIGHT (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 15 ) {
 if ( pi -> key_buffer != NULL ) {
 g_string_assign ( g_tmp , pi -> key_buffer ) ;
 g_string_truncate ( g_tmp , g_tmp -> len - 1 ) ;
 tmp_unistim_info -> key_buffer = g_strdup ( g_tmp -> str ) ;
 }
 comment = g_strdup_printf ( "Key Input Sent: LEFT (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 20 ) {
 comment = g_strdup_printf ( "Key Input Sent: S0 (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 21 ) {
 comment = g_strdup_printf ( "Key Input Sent: S1 (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 22 ) {
 if ( pi -> key_buffer != NULL ) {
 g_string_assign ( g_tmp , pi -> key_buffer ) ;
 g_string_truncate ( g_tmp , g_tmp -> len - 1 ) ;
 tmp_unistim_info -> key_buffer = g_strdup ( g_tmp -> str ) ;
 }
 comment = g_strdup_printf ( "Key Input Sent: S2 (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 28 ) {
 comment = g_strdup_printf ( "Key Input Sent: Release (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 23 ) {
 tmp_unistim_info -> key_buffer = g_strdup ( "\n" ) ;
 comment = g_strdup_printf ( "Key Input Sent: S3 (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 27 ) {
 comment = g_strdup_printf ( "Key Input Sent: Hold (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 29 ) {
 comment = g_strdup_printf ( "Key Input Sent: Mute (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 30 ) {
 comment = g_strdup_printf ( "Key Input Sent: Headset (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val == 31 ) {
 comment = g_strdup_printf ( "Key Input Sent: Handsfree (%d)" , pi -> sequence ) ;
 }
 else if ( pi -> key_val >= 32 && pi -> key_val <= 56 ) {
 comment = g_strdup_printf ( "Key Input Sent: Prog%d (%d)" , ( pi -> key_val & 31 ) , pi -> sequence ) ;
 }
 if ( pi -> key_val != - 1 ) {
 frame_label = "KEY INPUT" ;
 if ( comment == NULL ) comment = g_strdup_printf ( "Key Input Sent: UNKNOWN - %d (%d)" , pi -> key_val , pi -> sequence ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 g_free ( comment ) ;
 }
 if ( pi -> hook_state == 1 ) {
 frame_label = "OFF HOOK" ;
 comment = g_strdup_printf ( "Off Hook (%d)" , pi -> sequence ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 g_free ( comment ) ;
 }
 else if ( pi -> hook_state == 0 ) {
 frame_label = "ON HOOK" ;
 comment = g_strdup_printf ( "On Hook (%d)" , pi -> sequence ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 g_free ( comment ) ;
 }
 }
 if ( pi -> stream_connect == 1 && callsinfo != NULL ) {
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 if ( tmp_unistim_info -> key_buffer != NULL ) {
 callsinfo -> to_identity = g_strdup_printf ( "?? %s" , tmp_unistim_info -> key_buffer ) ;
 }
 tmp_unistim_info -> sequence = pi -> sequence ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_IN_CALL ;
 frame_label = "STREAM OPENED" ;
 comment = g_strdup_printf ( "Stream Opened (%d)" , pi -> sequence ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 }
 else if ( pi -> stream_connect == 1 && callsinfo == NULL ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_CALL_SETUP ;
 callsinfo -> from_identity = g_strdup ( "UNKNOWN" ) ;
 callsinfo -> to_identity = g_strdup ( "UNKNOWN" ) ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , & ( pinfo -> src ) ) ;
 callsinfo -> selected = FALSE ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> protocol = VOIP_UNISTIM ;
 callsinfo -> prot_info = g_malloc ( sizeof ( unistim_info_t ) ) ;
 tmp_unistim_info = ( unistim_info_t * ) callsinfo -> prot_info ;
 tmp_unistim_info -> rudp_type = 0 ;
 tmp_unistim_info -> payload_type = 0 ;
 tmp_unistim_info -> sequence = pi -> sequence ;
 tmp_unistim_info -> termid = 0 ;
 tmp_unistim_info -> key_val = - 1 ;
 tmp_unistim_info -> key_state = - 1 ;
 tmp_unistim_info -> hook_state = - 1 ;
 tmp_unistim_info -> stream_connect = - 1 ;
 tmp_unistim_info -> trans_connect = - 1 ;
 tmp_unistim_info -> set_termid = - 1 ;
 tmp_unistim_info -> string_data = NULL ;
 tmp_unistim_info -> key_buffer = NULL ;
 COPY_ADDRESS ( & ( tmp_unistim_info -> it_ip ) , & ( pi -> it_ip ) ) ;
 COPY_ADDRESS ( & ( tmp_unistim_info -> ni_ip ) , & ( pi -> ni_ip ) ) ;
 tmp_unistim_info -> it_port = pi -> it_port ;
 callsinfo -> free_prot_info = g_free ;
 callsinfo -> npackets = 0 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 if ( tmp_unistim_info -> key_buffer != NULL ) {
 callsinfo -> to_identity = g_strdup_printf ( "?? %s" , tmp_unistim_info -> key_buffer ) ;
 }
 tmp_unistim_info -> sequence = pi -> sequence ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_IN_CALL ;
 frame_label = "STREAM OPENED" ;
 comment = g_strdup_printf ( "Stream Opened (%d)" , pi -> sequence ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 }
 else if ( pi -> stream_connect == 0 && callsinfo != NULL ) {
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 tmp_unistim_info -> sequence = pi -> sequence ;
 if ( callsinfo -> call_state == VOIP_IN_CALL ) {
 callsinfo -> call_active_state = VOIP_INACTIVE ;
 callsinfo -> call_state = VOIP_COMPLETED ;
 }
 else {
 callsinfo -> call_state = VOIP_UNKNOWN ;
 callsinfo -> call_active_state = VOIP_INACTIVE ;
 }
 frame_label = "STREAM CLOSED" ;
 comment = g_strdup_printf ( "Stream Closed (%d)" , pi -> sequence ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 }
 else comment = NULL ;
 }
 else if ( pi -> rudp_type == 1 && callsinfo != NULL ) {
 if ( tmp_unistim_info -> sequence == pi -> sequence ) {
 frame_label = "ACK" ;
 comment = g_strdup_printf ( "ACK for sequence %d" , pi -> sequence ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 }
 }
 else if ( pi -> rudp_type == 0 && callsinfo != NULL ) {
 frame_label = "NAK" ;
 comment = g_strdup_printf ( "NAK for sequence %d" , pi -> sequence ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 }
 g_free ( comment ) ;
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }