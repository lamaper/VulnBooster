static int q931_calls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * q931_info ) {
 GList * list , * list2 ;
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 h323_calls_info_t * tmp_h323info , * tmp2_h323info ;
 actrace_isdn_calls_info_t * tmp_actrace_isdn_info ;
 voip_calls_info_t * tmp_listinfo ;
 voip_calls_info_t * callsinfo = NULL ;
 h245_address_t * h245_add = NULL ;
 gchar * comment ;
 const q931_packet_info * pi = ( const q931_packet_info * ) q931_info ;
 g_free ( q931_calling_number ) ;
 g_free ( q931_called_number ) ;
 if ( pi -> calling_number != NULL ) q931_calling_number = g_strdup ( pi -> calling_number ) ;
 else q931_calling_number = g_strdup ( "" ) ;
 if ( pi -> called_number != NULL ) q931_called_number = g_strdup ( pi -> called_number ) ;
 else q931_called_number = g_strdup ( "" ) ;
 q931_cause_value = pi -> cause_value ;
 q931_frame_num = pinfo -> fd -> num ;
 q931_crv = pi -> crv ;
 if ( h225_frame_num == q931_frame_num ) {
 tmp_h323info = NULL ;
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( ( tmp_listinfo -> protocol == VOIP_H323 ) && ( tmp_listinfo -> call_num == h225_call_num ) ) {
 tmp_h323info = ( h323_calls_info_t * ) tmp_listinfo -> prot_info ;
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 if ( tmp_h323info -> q931_crv == - 1 ) {
 tmp_h323info -> q931_crv = q931_crv ;
 }
 else if ( tmp_h323info -> q931_crv != q931_crv ) {
 tmp_h323info -> q931_crv2 = q931_crv ;
 }
 break ;
 }
 list = g_list_next ( list ) ;
 }
 if ( callsinfo != NULL ) {
 comment = NULL ;
 if ( h225_cstype == H225_SETUP ) {
 if ( q931_calling_number != NULL ) {
 g_free ( callsinfo -> from_identity ) ;
 callsinfo -> from_identity = g_strdup ( q931_calling_number ) ;
 }
 if ( q931_called_number != NULL ) {
 g_free ( callsinfo -> to_identity ) ;
 callsinfo -> to_identity = g_strdup ( q931_called_number ) ;
 }
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_H323 ) {
 tmp2_h323info = ( h323_calls_info_t * ) tmp_listinfo -> prot_info ;
 if ( ( strcmp ( callsinfo -> to_identity , tmp_listinfo -> to_identity ) == 0 ) && ( memcmp ( & tmp2_h323info -> guid , & guid_allzero , GUID_LEN ) == 0 ) ) {
 callsinfo -> npackets += change_call_num_graph ( tapinfo , tmp_listinfo -> call_num , callsinfo -> call_num ) ;
 g_free ( tmp_listinfo -> from_identity ) ;
 g_free ( tmp_listinfo -> to_identity ) ;
 DUMP_PTR2 ( tmp2_h323info -> guid ) ;
 g_free ( tmp2_h323info -> guid ) ;
 list2 = g_list_first ( tmp2_h323info -> h245_list ) ;
 while ( list2 ) {
 h245_add = ( h245_address_t * ) list2 -> data ;
 g_free ( ( void * ) h245_add -> h245_address . data ) ;
 g_free ( list2 -> data ) ;
 list2 = g_list_next ( list2 ) ;
 }
 g_list_free ( tmp_h323info -> h245_list ) ;
 tmp_h323info -> h245_list = NULL ;
 g_free ( tmp_listinfo -> prot_info ) ;
 tapinfo -> callsinfo_list = g_list_remove ( tapinfo -> callsinfo_list , tmp_listinfo ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 comment = g_strdup_printf ( "H225 From: %s To:%s TunnH245:%s FS:%s" , callsinfo -> from_identity , callsinfo -> to_identity , ( tmp_h323info -> is_h245Tunneling == TRUE ? "on" : "off" ) , ( h225_is_faststart == TRUE ? "on" : "off" ) ) ;
 }
 else if ( h225_cstype == H225_RELEASE_COMPLET ) {
 if ( q931_cause_value != 0xFF ) {
 comment = g_strdup_printf ( "H225 Q931 Rel Cause (%i):%s" , q931_cause_value , val_to_str_ext_const ( q931_cause_value , & q931_cause_code_vals_ext , "<unknown>" ) ) ;
 }
 else {
 comment = g_strdup ( "H225 No Q931 Rel Cause" ) ;
 }
 }
 if ( comment != NULL ) {
 change_frame_graph ( tapinfo , h225_frame_num , NULL , comment ) ;
 g_free ( comment ) ;
 }
 }
 h225_frame_num = 0 ;
 }
 else if ( h245_labels . frame_num == q931_frame_num ) {
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_H323 ) {
 tmp_h323info = ( h323_calls_info_t * ) tmp_listinfo -> prot_info ;
 if ( ( ( tmp_h323info -> q931_crv == q931_crv ) || ( tmp_h323info -> q931_crv2 == q931_crv ) ) && ( q931_crv != - 1 ) ) {
 if ( ! append_to_frame_graph ( tapinfo , q931_frame_num , NULL , NULL ) ) {
 add_to_graph ( tapinfo , pinfo , NULL , NULL , tmp_listinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 ++ ( tmp_listinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 }
 h245_add_to_graph ( pinfo -> fd -> num ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 }
 else {
 address pstn_add ;
 comment = NULL ;
 callsinfo = NULL ;
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_AC_ISDN ) {
 tmp_actrace_isdn_info = ( actrace_isdn_calls_info_t * ) tmp_listinfo -> prot_info ;
 if ( ( tmp_actrace_isdn_info -> crv == q931_crv ) && ( tmp_actrace_isdn_info -> trunk == actrace_trunk ) ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 SET_ADDRESS ( & pstn_add , AT_STRINGZ , 5 , g_strdup ( "PSTN" ) ) ;
 if ( ! callsinfo ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_CALL_SETUP ;
 callsinfo -> from_identity = g_strdup ( q931_calling_number ) ;
 callsinfo -> to_identity = g_strdup ( q931_called_number ) ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , actrace_direction ? & pstn_add : & ( pinfo -> src ) ) ;
 callsinfo -> selected = FALSE ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> protocol = VOIP_AC_ISDN ;
 callsinfo -> prot_info = g_malloc ( sizeof ( actrace_isdn_calls_info_t ) ) ;
 callsinfo -> free_prot_info = g_free ;
 tmp_actrace_isdn_info = ( actrace_isdn_calls_info_t * ) callsinfo -> prot_info ;
 tmp_actrace_isdn_info -> crv = q931_crv ;
 tmp_actrace_isdn_info -> trunk = actrace_trunk ;
 callsinfo -> npackets = 0 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 switch ( pi -> message_type ) {
 case Q931_SETUP : comment = g_strdup_printf ( "AC_ISDN trunk:%u Calling: %s Called:%s" , actrace_trunk , q931_calling_number , q931_called_number ) ;
 callsinfo -> call_state = VOIP_CALL_SETUP ;
 break ;
 case Q931_CONNECT : callsinfo -> call_state = VOIP_IN_CALL ;
 break ;
 case Q931_RELEASE_COMPLETE : case Q931_RELEASE : case Q931_DISCONNECT : if ( callsinfo -> call_state == VOIP_CALL_SETUP ) {
 if ( ADDRESSES_EQUAL ( & ( callsinfo -> initial_speaker ) , actrace_direction ? & pstn_add : & ( pinfo -> src ) ) ) {
 callsinfo -> call_state = VOIP_CANCELLED ;
 }
 else {
 callsinfo -> call_state = VOIP_REJECTED ;
 tapinfo -> rejected_calls ++ ;
 }
 }
 else if ( ( callsinfo -> call_state != VOIP_CANCELLED ) && ( callsinfo -> call_state != VOIP_REJECTED ) ) {
 callsinfo -> call_state = VOIP_COMPLETED ;
 tapinfo -> completed_calls ++ ;
 }
 if ( q931_cause_value != 0xFF ) {
 comment = g_strdup_printf ( "AC_ISDN trunk:%u Q931 Rel Cause (%i):%s" , actrace_trunk , q931_cause_value , val_to_str_ext_const ( q931_cause_value , & q931_cause_code_vals_ext , "<unknown>" ) ) ;
 }
 else {
 comment = g_strdup ( "AC_ISDN No Q931 Rel Cause" ) ;
 }
 break ;
 }
 if ( ! comment ) comment = g_strdup_printf ( "AC_ISDN trunk:%u" , actrace_trunk ) ;
 add_to_graph ( tapinfo , pinfo , val_to_str ( pi -> message_type , q931_message_type_vals , "<unknown>" ) , comment , callsinfo -> call_num , actrace_direction ? & pstn_add : & ( pinfo -> src ) , actrace_direction ? & ( pinfo -> src ) : & pstn_add , 1 ) ;
 g_free ( comment ) ;
 g_free ( ( char * ) pstn_add . data ) ;
 }
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }