static int H245dgcalls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * H245info ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 voip_calls_info_t * tmp_listinfo ;
 voip_calls_info_t * callsinfo = NULL ;
 h323_calls_info_t * tmp_h323info ;
 GList * list ;
 GList * list2 ;
 h245_address_t * h245_add = NULL ;
 const h245_packet_info * pi = ( const h245_packet_info * ) H245info ;
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == VOIP_H323 ) {
 tmp_h323info = ( h323_calls_info_t * ) tmp_listinfo -> prot_info ;
 list2 = g_list_first ( tmp_h323info -> h245_list ) ;
 while ( list2 ) {
 h245_add = ( h245_address_t * ) list2 -> data ;
 if ( ( ADDRESSES_EQUAL ( & ( h245_add -> h245_address ) , & ( pinfo -> src ) ) && ( h245_add -> h245_port == pinfo -> srcport ) ) || ( ADDRESSES_EQUAL ( & ( h245_add -> h245_address ) , & ( pinfo -> dst ) ) && ( h245_add -> h245_port == pinfo -> destport ) ) ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 break ;
 }
 list2 = g_list_next ( list2 ) ;
 }
 if ( callsinfo != NULL ) break ;
 }
 list = g_list_next ( list ) ;
 }
 if ( callsinfo != NULL ) {
 ++ ( callsinfo -> npackets ) ;
 ++ ( tapinfo -> npackets ) ;
 if ( ! append_to_frame_graph ( tapinfo , pinfo -> fd -> num , pi -> frame_label , pi -> comment ) ) {
 add_to_graph ( tapinfo , pinfo , pi -> frame_label , pi -> comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 }
 }
 else {
 h245_add_label ( pinfo -> fd -> num , ( gchar * ) pi -> frame_label , ( gchar * ) pi -> comment ) ;
 }
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }