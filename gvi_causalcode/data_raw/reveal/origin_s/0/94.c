static int dissect_dtap ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 static gsm_a_tap_rec_t tap_rec [ 4 ] ;
 static gsm_a_tap_rec_t * tap_p ;
 static guint tap_current = 0 ;
 void ( * dtap_msg_fcn ) ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len ) ;
 guint8 oct ;
 guint8 pd ;
 guint32 offset ;
 guint32 len ;
 guint32 oct_1 ;
 gint idx ;
 proto_item * dtap_item = NULL ;
 proto_tree * dtap_tree = NULL ;
 proto_item * oct_1_item = NULL ;
 proto_tree * pd_tree = NULL ;
 const gchar * msg_str ;
 gint ett_tree ;
 gint ti ;
 int hf_idx ;
 gboolean nsd ;
 sccp_msg_info_t * sccp_msg = ( sccp_msg_info_t * ) data ;
 len = tvb_reported_length ( tvb ) ;
 if ( len < 2 ) {
 call_data_dissector ( tvb , pinfo , tree ) ;
 return len ;
 }
 col_append_str ( pinfo -> cinfo , COL_INFO , "(DTAP) " ) ;
 tap_current ++ ;
 if ( tap_current >= 4 ) {
 tap_current = 0 ;
 }
 tap_p = & tap_rec [ tap_current ] ;
 offset = 0 ;
 g_tree = tree ;
 oct_1 = tvb_get_guint8 ( tvb , offset ++ ) ;
 if ( ( ( ( oct_1 & DTAP_TI_MASK ) >> 4 ) & DTAP_TIE_PRES_MASK ) == DTAP_TIE_PRES_MASK ) {
 offset ++ ;
 }
 oct = tvb_get_guint8 ( tvb , offset ) ;
 pd = oct_1 & DTAP_PD_MASK ;
 ti = - 1 ;
 msg_str = NULL ;
 ett_tree = - 1 ;
 hf_idx = - 1 ;
 dtap_msg_fcn = NULL ;
 nsd = FALSE ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "(%s) " , val_to_str_const ( pd , gsm_a_pd_short_str_vals , "unknown" ) ) ;
 switch ( pd ) {
 case 0 : msg_str = try_val_to_str_idx ( ( guint32 ) ( oct & DTAP_GCC_IEI_MASK ) , gsm_a_dtap_msg_gcc_strings , & idx ) ;
 if ( msg_str != NULL ) {
 ett_tree = ett_gsm_dtap_msg_gcc [ idx ] ;
 dtap_msg_fcn = dtap_msg_gcc [ idx ] ;
 }
 hf_idx = hf_gsm_a_dtap_msg_gcc_type ;
 ti = ( oct_1 & DTAP_TI_MASK ) >> 4 ;
 nsd = TRUE ;
 break ;
 case 1 : msg_str = try_val_to_str_idx ( ( guint32 ) ( oct & DTAP_BCC_IEI_MASK ) , gsm_a_dtap_msg_bcc_strings , & idx ) ;
 if ( msg_str != NULL ) {
 ett_tree = ett_gsm_dtap_msg_bcc [ idx ] ;
 dtap_msg_fcn = dtap_msg_bcc [ idx ] ;
 }
 hf_idx = hf_gsm_a_dtap_msg_bcc_type ;
 ti = ( oct_1 & DTAP_TI_MASK ) >> 4 ;
 nsd = TRUE ;
 break ;
 case 3 : msg_str = try_val_to_str_idx ( ( guint32 ) ( oct & DTAP_CC_IEI_MASK ) , gsm_a_dtap_msg_cc_strings , & idx ) ;
 if ( msg_str != NULL ) {
 ett_tree = ett_gsm_dtap_msg_cc [ idx ] ;
 dtap_msg_fcn = dtap_msg_cc_fcn [ idx ] ;
 }
 hf_idx = hf_gsm_a_dtap_msg_cc_type ;
 ti = ( oct_1 & DTAP_TI_MASK ) >> 4 ;
 nsd = TRUE ;
 break ;
 case 5 : msg_str = try_val_to_str_idx ( ( guint32 ) ( oct & DTAP_MM_IEI_MASK ) , gsm_a_dtap_msg_mm_strings , & idx ) ;
 if ( msg_str != NULL ) {
 ett_tree = ett_gsm_dtap_msg_mm [ idx ] ;
 dtap_msg_fcn = dtap_msg_mm_fcn [ idx ] ;
 }
 hf_idx = hf_gsm_a_dtap_msg_mm_type ;
 nsd = TRUE ;
 break ;
 case 6 : get_rr_msg_params ( oct , & msg_str , & ett_tree , & hf_idx , & dtap_msg_fcn ) ;
 break ;
 case 8 : get_gmm_msg_params ( oct , & msg_str , & ett_tree , & hf_idx , & dtap_msg_fcn ) ;
 break ;
 case 9 : msg_str = try_val_to_str_idx ( ( guint32 ) ( oct & DTAP_SMS_IEI_MASK ) , gsm_a_dtap_msg_sms_strings , & idx ) ;
 hf_idx = hf_gsm_a_dtap_msg_sms_type ;
 if ( msg_str != NULL ) {
 ett_tree = ett_gsm_dtap_msg_sms [ idx ] ;
 dtap_msg_fcn = dtap_msg_sms_fcn [ idx ] ;
 }
 ti = ( oct_1 & DTAP_TI_MASK ) >> 4 ;
 break ;
 case 10 : get_sm_msg_params ( oct , & msg_str , & ett_tree , & hf_idx , & dtap_msg_fcn ) ;
 ti = ( oct_1 & DTAP_TI_MASK ) >> 4 ;
 break ;
 case 11 : msg_str = try_val_to_str_idx ( ( guint32 ) ( oct & DTAP_SS_IEI_MASK ) , gsm_a_dtap_msg_ss_strings , & idx ) ;
 hf_idx = hf_gsm_a_dtap_msg_ss_type ;
 if ( msg_str != NULL ) {
 ett_tree = ett_gsm_dtap_msg_ss [ idx ] ;
 dtap_msg_fcn = dtap_msg_ss_fcn [ idx ] ;
 }
 ti = ( oct_1 & DTAP_TI_MASK ) >> 4 ;
 nsd = TRUE ;
 break ;
 case 15 : msg_str = try_val_to_str_idx ( ( guint32 ) ( oct & DTAP_TP_IEI_MASK ) , gsm_a_dtap_msg_tp_strings , & idx ) ;
 hf_idx = hf_gsm_a_dtap_msg_tp_type ;
 if ( msg_str != NULL ) {
 ett_tree = ett_gsm_dtap_msg_tp [ idx ] ;
 dtap_msg_fcn = dtap_msg_tp_fcn [ idx ] ;
 }
 nsd = TRUE ;
 break ;
 default : return len ;
 }
 if ( sccp_msg && sccp_msg -> data . co . assoc ) {
 sccp_assoc = sccp_msg -> data . co . assoc ;
 }
 else {
 sccp_assoc = NULL ;
 sccp_msg = NULL ;
 }
 if ( msg_str == NULL ) {
 dtap_item = proto_tree_add_protocol_format ( tree , proto_a_dtap , tvb , 0 , len , "GSM A-I/F DTAP - Unknown DTAP Message Type (0x%02x)" , oct ) ;
 dtap_tree = proto_item_add_subtree ( dtap_item , ett_dtap_msg ) ;
 if ( sccp_msg && ! sccp_msg -> data . co . label ) {
 sccp_msg -> data . co . label = wmem_strdup_printf ( wmem_file_scope ( ) , "DTAP (0x%02x)" , oct ) ;
 }
 }
 else {
 dtap_item = proto_tree_add_protocol_format ( tree , proto_a_dtap , tvb , 0 , - 1 , "GSM A-I/F DTAP - %s" , msg_str ) ;
 dtap_tree = proto_item_add_subtree ( dtap_item , ett_tree ) ;
 if ( sccp_msg && ! sccp_msg -> data . co . label ) {
 sccp_msg -> data . co . label = wmem_strdup ( wmem_file_scope ( ) , msg_str ) ;
 }
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s " , msg_str ) ;
 col_set_fence ( pinfo -> cinfo , COL_INFO ) ;
 }
 oct_1_item = proto_tree_add_uint ( dtap_tree , hf_gsm_a_dtap_protocol_discriminator , tvb , 0 , 1 , pd ) ;
 pd_tree = proto_item_add_subtree ( oct_1_item , ett_dtap_oct_1 ) ;
 proto_tree_add_item ( pd_tree , hf_gsm_a_L3_protocol_discriminator , tvb , 0 , 1 , ENC_BIG_ENDIAN ) ;
 if ( ti == - 1 ) {
 proto_tree_add_item ( pd_tree , hf_gsm_a_skip_ind , tvb , 0 , 1 , ENC_BIG_ENDIAN ) ;
 }
 else {
 proto_tree_add_item ( pd_tree , hf_gsm_a_dtap_ti_flag , tvb , 0 , 1 , ENC_NA ) ;
 if ( ( ti & DTAP_TIE_PRES_MASK ) == DTAP_TIE_PRES_MASK ) {
 proto_tree_add_uint_format_value ( pd_tree , hf_gsm_a_dtap_tio , tvb , 0 , 1 , oct_1 , "The TI value is given by the TIE in octet 2" ) ;
 }
 else {
 proto_tree_add_item ( pd_tree , hf_gsm_a_dtap_tio , tvb , 0 , 1 , ENC_BIG_ENDIAN ) ;
 }
 }
 if ( ( ti != - 1 ) && ( ti & DTAP_TIE_PRES_MASK ) == DTAP_TIE_PRES_MASK ) {
 proto_tree_add_item ( tree , hf_gsm_a_extension , tvb , 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( pd_tree , hf_gsm_a_dtap_tie , tvb , 1 , 1 , ENC_BIG_ENDIAN ) ;
 }
 if ( ( pinfo -> p2p_dir == P2P_DIR_RECV ) && nsd ) {
 }
 if ( ( pd == 5 ) || ( pd == 3 ) || ( pd == 10 ) || ( pd == 11 ) ) {
 proto_tree_add_item ( dtap_tree , hf_gsm_a_seq_no , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_item ( dtap_tree , hf_idx , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 tap_p -> pdu_type = GSM_A_PDU_TYPE_DTAP ;
 tap_p -> message_type = ( nsd ? ( oct & 0x3f ) : oct ) ;
 tap_p -> protocol_disc = ( gsm_a_pd_str_e ) pd ;
 tap_queue_packet ( gsm_a_tap , pinfo , tap_p ) ;
 if ( msg_str == NULL ) return len ;
 if ( offset >= len ) return len ;
 if ( dtap_msg_fcn == NULL ) {
 proto_tree_add_item ( dtap_tree , hf_gsm_a_dtap_message_elements , tvb , offset , len - offset , ENC_NA ) ;
 }
 else {
 ( * dtap_msg_fcn ) ( tvb , dtap_tree , pinfo , offset , len - offset ) ;
 }
 return len ;
 }