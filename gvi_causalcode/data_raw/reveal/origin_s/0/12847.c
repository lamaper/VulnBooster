static int sccp_calls ( packet_info * pinfo , const void * prot_info ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 const sccp_msg_info_t * msg = ( const sccp_msg_info_t * ) prot_info ;
 sccp_assoc_info_t * assoc = msg -> data . co . assoc ;
 GList * list ;
 voip_calls_info_t * callsinfo = NULL ;
 const gchar * label = NULL ;
 const gchar * comment = NULL ;
 for ( list = g_list_first ( tapinfo -> callsinfo_list ) ;
 list ;
 list = g_list_next ( list ) ) {
 if ( ( ( voip_calls_info_t * ) ( list -> data ) ) -> prot_info == assoc ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 if ( callsinfo == NULL ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_state = VOIP_CALL_SETUP ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 if ( assoc -> calling_party ) {
 callsinfo -> from_identity = g_strdup ( assoc -> calling_party ) ;
 }
 else {
 callsinfo -> from_identity = g_strdup ( "Unknown" ) ;
 }
 if ( assoc -> called_party ) {
 callsinfo -> to_identity = g_strdup ( assoc -> called_party ) ;
 }
 else {
 callsinfo -> to_identity = g_strdup ( "Unknown" ) ;
 }
 callsinfo -> prot_info = ( void * ) assoc ;
 callsinfo -> free_prot_info = NULL ;
 callsinfo -> npackets = 1 ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , & ( pinfo -> src ) ) ;
 callsinfo -> protocol = SP2VP ( assoc -> payload ) ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 callsinfo -> selected = FALSE ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 else {
 if ( assoc -> calling_party ) {
 g_free ( callsinfo -> from_identity ) ;
 callsinfo -> from_identity = g_strdup ( assoc -> calling_party ) ;
 }
 if ( assoc -> called_party ) {
 g_free ( callsinfo -> to_identity ) ;
 callsinfo -> to_identity = g_strdup ( assoc -> called_party ) ;
 }
 callsinfo -> protocol = SP2VP ( assoc -> payload ) ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 switch ( msg -> type ) {
 case SCCP_MSG_TYPE_CC : callsinfo -> call_state = VOIP_IN_CALL ;
 break ;
 case SCCP_MSG_TYPE_RLC : callsinfo -> call_state = VOIP_COMPLETED ;
 callsinfo -> call_active_state = VOIP_INACTIVE ;
 break ;
 default : break ;
 }
 }
 if ( msg -> data . co . label ) {
 label = msg -> data . co . label ;
 }
 else {
 label = val_to_str ( msg -> type , sccp_payload_values , "Unknown(%d)" ) ;
 }
 if ( msg -> data . co . comment ) {
 comment = msg -> data . co . comment ;
 }
 else {
 comment = NULL ;
 }
 add_to_graph ( tapinfo , pinfo , label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 ++ ( tapinfo -> npackets ) ;
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }