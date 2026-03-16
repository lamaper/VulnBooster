static int h248_calls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * prot_info ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 const gcp_cmd_t * cmd = ( const gcp_cmd_t * ) prot_info ;
 GList * list ;
 voip_calls_info_t * callsinfo = NULL ;
 address * mgw ;
 address * mgc ;
 gchar mgw_addr [ 128 ] ;
 if ( cmd -> ctx -> id == NULL_CONTEXT || cmd -> ctx -> id == ALL_CONTEXTS ) {
 return 0 ;
 }
 if ( gcp_is_req ( cmd -> type ) ) {
 mgw = & ( pinfo -> dst ) ;
 mgc = & ( pinfo -> src ) ;
 }
 else {
 mgc = & ( pinfo -> dst ) ;
 mgw = & ( pinfo -> src ) ;
 }
 address_to_str_buf ( mgw , mgw_addr , 128 ) ;
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 voip_calls_info_t * tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( tmp_listinfo -> protocol == TEL_H248 ) {
 if ( tmp_listinfo -> prot_info == cmd -> ctx ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 list = g_list_next ( list ) ;
 }
 if ( callsinfo == NULL ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_state = VOIP_NO_STATE ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> from_identity = g_strdup_printf ( "%s : %.8x" , mgw_addr , cmd -> ctx -> id ) ;
 callsinfo -> to_identity = g_strdup ( "" ) ;
 callsinfo -> prot_info = cmd -> ctx ;
 callsinfo -> free_prot_info = NULL ;
 callsinfo -> npackets = 1 ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , mgc ) ;
 callsinfo -> protocol = TEL_H248 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 callsinfo -> selected = FALSE ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 else {
 GString * s = g_string_new ( "" ) ;
 gcp_terms_t * ctx_term ;
 g_free ( callsinfo -> from_identity ) ;
 callsinfo -> from_identity = g_strdup_printf ( "%s : %.8x" , mgw_addr , ( ( gcp_ctx_t * ) callsinfo -> prot_info ) -> id ) ;
 g_free ( callsinfo -> to_identity ) ;
 for ( ctx_term = ( ( gcp_ctx_t * ) callsinfo -> prot_info ) -> terms . next ;
 ctx_term ;
 ctx_term = ctx_term -> next ) {
 if ( ctx_term -> term && ctx_term -> term -> str ) {
 g_string_append_printf ( s , " %s" , ctx_term -> term -> str ) ;
 }
 }
 callsinfo -> to_identity = s -> str ;
 g_string_free ( s , FALSE ) ;
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 }
 add_to_graph ( tapinfo , pinfo , cmd -> str ? cmd -> str : "unknown Msg" , ep_strdup_printf ( "TrxId = %u, CtxId = %.8x" , cmd -> trx -> id , cmd -> ctx -> id ) , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 ++ ( tapinfo -> npackets ) ;
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }