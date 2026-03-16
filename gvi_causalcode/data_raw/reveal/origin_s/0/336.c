static int isup_calls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * isup_info _U_ ) {
 voip_calls_tapinfo_t * tapinfo = & the_tapinfo_struct ;
 voip_calls_info_t * tmp_listinfo ;
 voip_calls_info_t * callsinfo = NULL ;
 isup_calls_info_t * tmp_isupinfo ;
 gboolean found = FALSE ;
 gboolean forward = FALSE ;
 gboolean right_pair ;
 GList * list ;
 gchar * frame_label = NULL ;
 gchar * comment = NULL ;
 const isup_tap_rec_t * pi = ( const isup_tap_rec_t * ) isup_info ;
 if ( mtp3_frame_num != pinfo -> fd -> num ) return 0 ;
 list = g_list_first ( tapinfo -> callsinfo_list ) ;
 while ( list ) {
 right_pair = TRUE ;
 tmp_listinfo = ( voip_calls_info_t * ) list -> data ;
 if ( ( tmp_listinfo -> protocol == VOIP_ISUP ) && ( tmp_listinfo -> call_active_state == VOIP_ACTIVE ) ) {
 tmp_isupinfo = ( isup_calls_info_t * ) tmp_listinfo -> prot_info ;
 if ( ( tmp_isupinfo -> cic == pinfo -> circuit_id ) && ( tmp_isupinfo -> ni == mtp3_ni ) ) {
 if ( ( tmp_isupinfo -> opc == mtp3_opc ) && ( tmp_isupinfo -> dpc == mtp3_dpc ) ) {
 forward = TRUE ;
 }
 else if ( ( tmp_isupinfo -> dpc == mtp3_opc ) && ( tmp_isupinfo -> opc == mtp3_dpc ) ) {
 forward = FALSE ;
 }
 else {
 right_pair = FALSE ;
 }
 if ( right_pair ) {
 if ( tmp_listinfo -> call_state == VOIP_CALL_SETUP ) {
 found = TRUE ;
 }
 else if ( pi -> message_type != 1 ) {
 found = TRUE ;
 }
 else {
 tmp_listinfo -> call_active_state = VOIP_INACTIVE ;
 }
 }
 if ( found ) {
 callsinfo = ( voip_calls_info_t * ) ( list -> data ) ;
 break ;
 }
 }
 }
 list = g_list_next ( list ) ;
 }
 if ( ( callsinfo == NULL ) && ( pi -> message_type == 1 ) ) {
 callsinfo = ( voip_calls_info_t * ) g_malloc0 ( sizeof ( voip_calls_info_t ) ) ;
 callsinfo -> call_active_state = VOIP_ACTIVE ;
 callsinfo -> call_state = VOIP_UNKNOWN ;
 COPY_ADDRESS ( & ( callsinfo -> initial_speaker ) , & ( pinfo -> src ) ) ;
 callsinfo -> selected = FALSE ;
 callsinfo -> start_fd = pinfo -> fd ;
 callsinfo -> start_rel_ts = pinfo -> rel_ts ;
 callsinfo -> protocol = VOIP_ISUP ;
 if ( pi -> calling_number != NULL ) {
 callsinfo -> from_identity = g_strdup ( pi -> calling_number ) ;
 }
 if ( pi -> called_number != NULL ) {
 callsinfo -> to_identity = g_strdup ( pi -> called_number ) ;
 }
 callsinfo -> prot_info = g_malloc ( sizeof ( isup_calls_info_t ) ) ;
 callsinfo -> free_prot_info = g_free ;
 tmp_isupinfo = ( isup_calls_info_t * ) callsinfo -> prot_info ;
 tmp_isupinfo -> opc = mtp3_opc ;
 tmp_isupinfo -> dpc = mtp3_dpc ;
 tmp_isupinfo -> ni = mtp3_ni ;
 tmp_isupinfo -> cic = pinfo -> circuit_id ;
 callsinfo -> npackets = 0 ;
 callsinfo -> call_num = tapinfo -> ncalls ++ ;
 tapinfo -> callsinfo_list = g_list_prepend ( tapinfo -> callsinfo_list , callsinfo ) ;
 }
 if ( callsinfo != NULL ) {
 callsinfo -> stop_fd = pinfo -> fd ;
 callsinfo -> stop_rel_ts = pinfo -> rel_ts ;
 ++ ( callsinfo -> npackets ) ;
 frame_label = g_strdup ( val_to_str_ext_const ( pi -> message_type , & isup_message_type_value_acro_ext , "Unknown" ) ) ;
 if ( callsinfo -> npackets == 1 ) {
 if ( ( pi -> calling_number != NULL ) && ( pi -> called_number != NULL ) ) {
 comment = g_strdup_printf ( "Call from %s to %s" , pi -> calling_number , pi -> called_number ) ;
 }
 }
 else if ( callsinfo -> npackets == 2 ) {
 if ( forward ) {
 comment = g_strdup_printf ( "%i-%i -> %i-%i. Cic:%i" , mtp3_ni , mtp3_opc , mtp3_ni , mtp3_dpc , pinfo -> circuit_id ) ;
 }
 else {
 comment = g_strdup_printf ( "%i-%i -> %i-%i. Cic:%i" , mtp3_ni , mtp3_dpc , mtp3_ni , mtp3_opc , pinfo -> circuit_id ) ;
 }
 }
 switch ( pi -> message_type ) {
 case 1 : callsinfo -> call_state = VOIP_CALL_SETUP ;
 break ;
 case 7 : case 9 : callsinfo -> call_state = VOIP_IN_CALL ;
 break ;
 case 12 : if ( callsinfo -> call_state == VOIP_CALL_SETUP ) {
 if ( forward ) {
 callsinfo -> call_state = VOIP_CANCELLED ;
 }
 else {
 callsinfo -> call_state = VOIP_REJECTED ;
 tapinfo -> rejected_calls ++ ;
 }
 }
 else if ( callsinfo -> call_state == VOIP_IN_CALL ) {
 callsinfo -> call_state = VOIP_COMPLETED ;
 tapinfo -> completed_calls ++ ;
 }
 comment = g_strdup_printf ( "Cause %i - %s" , pi -> cause_value , val_to_str_ext_const ( pi -> cause_value , & q931_cause_code_vals_ext , "(Unknown)" ) ) ;
 break ;
 }
 ++ ( tapinfo -> npackets ) ;
 add_to_graph ( tapinfo , pinfo , frame_label , comment , callsinfo -> call_num , & ( pinfo -> src ) , & ( pinfo -> dst ) , 1 ) ;
 g_free ( comment ) ;
 g_free ( frame_label ) ;
 }
 tapinfo -> redraw = TRUE ;
 return 1 ;
 }