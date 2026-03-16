static int iax2_calls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * iax2_info ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 GList * list ;
 voip_calls_info_t * callsinfo = NULL ;
 address * phone ;
 const iax2_info_t * ii = ( const iax2_info_t * ) iax2_info ;
 iax2_info_t * tmp_iax2info ;
 if ( ii == NULL || ii -> ptype != IAX2_FULL_PACKET || ( ii -> scallno == 0 && ii -> dcallno == 0 ) ) return 0 ;
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 voip_calls_info_t * tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_IAX2 ) {
 tmp_iax2info = ( iax2_info_t * ) tmp_listinfo -> prot_info ;
 if ( tmp_iax2info -> scallno == ii -> scallno || tmp_iax2info -> scallno == ii -> dcallno ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 phone = & ( pinfo -> src ) ;
 if ( callsinfo == NULL ) {
 if ( ii -> ftype != AST_FRAME_IAX || ii -> csub != IAX_COMMAND_NEW ) return 0 ;
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_state = VOIP_NO_STATE ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> prot_info = g_malloc ( sizeof ( iax2_info_t ) ) ;
 callsinfo -> free_prot_info = free_iax2_info ;
 tmp_iax2info = ( iax2_info_t * ) callsinfo -> prot_info ;
 tmp_iax2info -> scallno = ii -> scallno ;
 if ( tmp_iax2info -> scallno == 0 ) tmp_iax2info -> scallno = ii -> dcallno ;
 tmp_iax2info -> callState = ii -> callState ;
 callsinfo -> npackets = 1 ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , phone ) ;
 callsinfo -> from_identity = g_strdup ( ii -> callingParty ) ;
 callsinfo -> to_identity = g_strdup ( ii -> calledParty ) ;
 callsinfo -> protocol = VOIP_IAX2 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 callsinfo -> selected = FALSE ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 else {
 callsinfo -> call_state = ii -> callState ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 }
 add_to_graph ( tapinfo , pinfo , ii -> messageName , "" , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 return 1 ;
 }