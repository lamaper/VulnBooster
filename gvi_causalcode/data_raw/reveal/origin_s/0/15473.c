static int skinny_calls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * skinny_info ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 GList * list ;
 voip_calls_info_t * callsinfo = NULL ;
 address * phone ;
 const skinny_info_t * si = ( const skinny_info_t * ) skinny_info ;
 skinny_calls_info_t * tmp_skinnyinfo ;
 gchar * comment ;
 if ( si == NULL || ( si -> callId == 0 && si -> passThruId == 0 ) ) return 0 ;
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 voip_calls_info_t * tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_SKINNY ) {
 tmp_skinnyinfo = ( skinny_calls_info_t * ) tmp_listinfo -> prot_info ;
 if ( tmp_skinnyinfo -> callId == si -> callId || tmp_skinnyinfo -> callId == si -> passThruId ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 if ( si -> messId >= 256 ) phone = & ( pinfo -> dst ) ;
 else phone = & ( pinfo -> src ) ;
 if ( callsinfo == NULL ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_state = VOIP_NO_STATE ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> from_identity = g_strdup ( "" ) ;
 callsinfo -> to_identity = g_strdup ( "" ) ;
 callsinfo -> prot_info = g_malloc ( sizeof ( skinny_calls_info_t ) ) ;
 callsinfo -> free_prot_info = g_free ;
 tmp_skinnyinfo = ( skinny_calls_info_t * ) callsinfo -> prot_info ;
 tmp_skinnyinfo -> callId = si -> callId ? si -> callId : si -> passThruId ;
 callsinfo -> npackets = 1 ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , phone ) ;
 callsinfo -> protocol = VOIP_SKINNY ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 callsinfo -> selected = FALSE ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 else {
 if ( si -> callingParty ) {
 g_free ( callsinfo -> from_identity ) ;
 callsinfo -> from_identity = g_strdup ( si -> callingParty ) ;
 }
 if ( si -> calledParty ) {
 g_free ( callsinfo -> to_identity ) ;
 callsinfo -> to_identity = g_strdup ( si -> calledParty ) ;
 }
 if ( ( si -> callState > 0 ) && ( si -> callState < ( sizeof ( skinny_tap_voip_state ) / sizeof ( skinny_tap_voip_state [ 0 ] ) ) ) ) callsinfo -> call_state = skinny_tap_voip_state [ si -> callState ] ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 }
 if ( si -> callId ) {
 if ( si -> passThruId ) comment = g_strdup_printf ( "CallId = %u, PTId = %u" , si -> callId , si -> passThruId ) ;
 else comment = g_strdup_printf ( "CallId = %u, LineId = %u" , si -> callId , si -> lineId ) ;
 }
 else {
 if ( si -> passThruId ) comment = g_strdup_printf ( "PTId = %u" , si -> passThruId ) ;
 else comment = NULL ;
 }
 add_to_graph ( tapinfo , pinfo , si -> messageName , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 g_free ( comment ) ;
 return 1 ;
 }