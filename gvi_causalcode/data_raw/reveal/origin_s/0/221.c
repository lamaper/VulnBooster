static int H225calls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * H225info ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 voip_calls_info_t * tmp_listinfo ;
 voip_calls_info_t * callsinfo = NULL ;
 h323_calls_info_t * tmp_h323info = NULL ;
 gchar * frame_label ;
 gchar * comment ;
 GList * list ;
 h245_address_t * h245_add = NULL ;
 const h225_packet_info * pi = ( const h225_packet_info * ) H225info ;
 if ( ( memcmp ( & pi -> guid , & guid_allzero , GUID_LEN ) == 0 ) ) if ( ( ( pi -> msg_type == H225_RAS ) && ( ( pi -> msg_tag < 18 ) || ( pi -> msg_tag > 20 ) ) ) || ( pi -> msg_type != H225_RAS ) ) return 0 ;
 if ( ( pi -> msg_type == H225_RAS ) && ( ( pi -> msg_tag == 19 ) || ( pi -> msg_tag == 20 ) ) ) {
 if ( ! pi -> request_available ) return 0 ;
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 g_assert ( tmp_listinfo != NULL ) ;
 if ( tmp_listinfo -> protocol == VOIP_H323 ) {
 tmp_h323info = ( h323_calls_info_t * ) tmp_listinfo -> prot_info ;
 if ( tmp_h323info -> requestSeqNum == pi -> requestSeqNum ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 }
 else {
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_H323 ) {
 tmp_h323info = ( h323_calls_info_t * ) tmp_listinfo -> prot_info ;
 g_assert ( tmp_h323info != NULL ) ;
 if ( ( memcmp ( tmp_h323info -> guid , & guid_allzero , GUID_LEN ) != 0 ) && ( memcmp ( tmp_h323info -> guid , & pi -> guid , GUID_LEN ) == 0 ) ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 }
 h225_cstype = pi -> cs_type ;
 h225_is_faststart = pi -> is_faststart ;
 if ( callsinfo == NULL ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_UNKNOWN ;
 callsinfo -> from_identity = g_strdup ( "" ) ;
 callsinfo -> to_identity = g_strdup ( "" ) ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , & ( pinfo -> src ) ) ;
 callsinfo -> selected = FALSE ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> protocol = VOIP_H323 ;
 callsinfo -> prot_info = g_malloc ( sizeof ( h323_calls_info_t ) ) ;
 callsinfo -> free_prot_info = free_h225_info ;
 tmp_h323info = ( h323_calls_info_t * ) callsinfo -> prot_info ;
 g_assert ( tmp_h323info != NULL ) ;
 tmp_h323info -> guid = ( e_guid_t * ) g_memdup ( & pi -> guid , sizeof pi -> guid ) ;
 DUMP_PTR1 ( tmp_h323info -> guid ) ;
 tmp_h323info -> h225SetupAddr . type = AT_NONE ;
 tmp_h323info -> h225SetupAddr . len = 0 ;
 tmp_h323info -> h245_list = NULL ;
 tmp_h323info -> is_faststart_Setup = FALSE ;
 tmp_h323info -> is_faststart_Proc = FALSE ;
 tmp_h323info -> is_h245Tunneling = FALSE ;
 tmp_h323info -> is_h245 = FALSE ;
 tmp_h323info -> q931_crv = - 1 ;
 tmp_h323info -> q931_crv2 = - 1 ;
 tmp_h323info -> requestSeqNum = 0 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 callsinfo -> npackets = 0 ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 h225_frame_num = pinfo -> fd -> num ;
 h225_call_num = callsinfo -> call_num ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 g_assert ( tmp_h323info != NULL ) ;
 if ( pi -> msg_type == H225_CS ) {
 if ( pi -> is_h245 == TRUE ) {
 h245_add = ( h245_address_t * ) g_malloc ( sizeof ( h245_address_t ) ) ;
 h245_add -> h245_address . type = AT_IPv4 ;
 h245_add -> h245_address . len = 4 ;
 h245_add -> h245_address . data = g_malloc ( sizeof ( pi -> h245_address ) ) ;
 memcpy ( ( void * ) ( h245_add -> h245_address . data ) , & ( pi -> h245_address ) , 4 ) ;
 h245_add -> h245_port = pi -> h245_port ;
 add_h245_Address ( tmp_h323info , h245_add ) ;
 }
 if ( pi -> cs_type != H225_RELEASE_COMPLET ) tmp_h323info -> is_h245Tunneling = pi -> is_h245Tunneling ;
 frame_label = g_strdup ( pi -> frame_label ) ;
 switch ( pi -> cs_type ) {
 case H225_SETUP : tmp_h323info -> is_faststart_Setup = pi -> is_faststart ;
 if ( tmp_h323info -> h225SetupAddr . type == AT_NONE ) COPY_ADDRESS ( & ( tmp_h323info -> h225SetupAddr ) , & ( pinfo -> src ) ) ;
 callsinfo -> call_state = VOIP_CALL_SETUP ;
 comment = g_strdup_printf ( "H225 TunnH245:%s FS:%s" , ( tmp_h323info -> is_h245Tunneling == TRUE ? "on" : "off" ) , ( pi -> is_faststart == TRUE ? "on" : "off" ) ) ;
 break ;
 case H225_CONNECT : callsinfo -> call_state = VOIP_IN_CALL ;
 if ( pi -> is_faststart == TRUE ) tmp_h323info -> is_faststart_Proc = TRUE ;
 comment = g_strdup_printf ( "H225 TunnH245:%s FS:%s" , ( tmp_h323info -> is_h245Tunneling == TRUE ? "on" : "off" ) , ( pi -> is_faststart == TRUE ? "on" : "off" ) ) ;
 break ;
 case H225_RELEASE_COMPLET : if ( callsinfo -> call_state == VOIP_CALL_SETUP ) {
 if ( ADDRESSES_EQUAL ( & ( tmp_h323info -> h225SetupAddr ) , & ( pinfo -> src ) ) ) {
 callsinfo -> call_state = VOIP_CANCELLED ;
 }
 else {
 callsinfo -> call_state = VOIP_REJECTED ;
 tapinfo -> rejected_calls ++ ;
 }
 }
 else {
 callsinfo -> call_state = VOIP_COMPLETED ;
 tapinfo -> completed_calls ++ ;
 }
 comment = g_strdup ( "H225 No Q931 Rel Cause" ) ;
 break ;
 case H225_PROGRESS : case H225_ALERTING : case H225_CALL_PROCEDING : if ( pi -> is_faststart == TRUE ) tmp_h323info -> is_faststart_Proc = TRUE ;
 comment = g_strdup_printf ( "H225 TunnH245:%s FS:%s" , ( tmp_h323info -> is_h245Tunneling == TRUE ? "on" : "off" ) , ( pi -> is_faststart == TRUE ? "on" : "off" ) ) ;
 break ;
 default : comment = g_strdup_printf ( "H225 TunnH245:%s FS:%s" , ( tmp_h323info -> is_h245Tunneling == TRUE ? "on" : "off" ) , ( pi -> is_faststart == TRUE ? "on" : "off" ) ) ;
 }
 }
 else if ( pi -> msg_type == H225_RAS ) {
 switch ( pi -> msg_tag ) {
 case 18 : if ( ! pi -> is_duplicate ) {
 g_free ( callsinfo -> to_identity ) ;
 callsinfo -> to_identity = g_strdup ( pi -> dialedDigits ) ;
 tmp_h323info -> requestSeqNum = pi -> requestSeqNum ;
 }
 case 19 : if ( strlen ( pi -> dialedDigits ) ) comment = g_strdup_printf ( "H225 RAS dialedDigits: %s" , pi -> dialedDigits ) ;
 else comment = g_strdup ( "H225 RAS" ) ;
 break ;
 default : comment = g_strdup ( "H225 RAS" ) ;
 }
 frame_label = g_strdup ( val_to_str_const ( pi -> msg_tag , h225_RasMessage_vals , "<unknown>" ) ) ;
 }
 else {
 frame_label = g_strdup ( "H225: Unknown" ) ;
 comment = NULL ;
 }
 if ( ! append_to_frame_graph ( tapinfo , pinfo -> fd -> num , pi -> frame_label , comment ) ) {
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 }
 h245_add_to_graph ( pinfo -> fd -> num ) ;
 g_free ( frame_label ) ;
 g_free ( comment ) ;
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }