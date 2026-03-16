static void dissect_rsvp_msg_tree ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int tree_mode , rsvp_conversation_info * rsvph , gboolean e2ei ) {
 proto_tree * rsvp_tree ;
 proto_tree * rsvp_header_tree ;
 proto_tree * rsvp_object_tree ;
 proto_tree * ti , * len_item ;
 proto_item * hidden_item , * cksum_item ;
 guint16 cksum , computed_cksum ;
 vec_t cksum_vec [ 1 ] ;
 int offset = 0 ;
 int len ;
 guint8 message_type ;
 int session_off , tempfilt_off ;
 int msg_length ;
 int obj_length ;
 gboolean have_integrity_object = FALSE ;
 offset = 0 ;
 msg_length = tvb_get_ntohs ( tvb , 6 ) ;
 message_type = tvb_get_guint8 ( tvb , 1 ) ;
 ti = proto_tree_add_item ( tree , proto_rsvp , tvb , offset , msg_length , ENC_NA ) ;
 rsvp_tree = proto_item_add_subtree ( ti , tree_mode ) ;
 if ( e2ei ) proto_item_append_text ( rsvp_tree , " (E2E-IGNORE)" ) ;
 proto_item_append_text ( rsvp_tree , ": " ) ;
 proto_item_append_text ( rsvp_tree , "%s" , val_to_str_ext ( message_type , & message_type_vals_ext , "Unknown (%u). " ) ) ;
 find_rsvp_session_tempfilt ( tvb , 0 , & session_off , & tempfilt_off ) ;
 if ( session_off ) proto_item_append_text ( rsvp_tree , "%s" , summary_session ( tvb , session_off ) ) ;
 if ( tempfilt_off ) proto_item_append_text ( rsvp_tree , "%s" , summary_template ( tvb , tempfilt_off ) ) ;
 rsvp_header_tree = proto_tree_add_subtree_format ( rsvp_tree , tvb , offset , 8 , TREE ( TT_HDR ) , & ti , "RSVP Header. %s" , val_to_str_ext ( message_type , & message_type_vals_ext , "Unknown Message (%u). " ) ) ;
 if ( e2ei ) proto_item_append_text ( ti , " (E2E-IGNORE)" ) ;
 proto_tree_add_item ( rsvp_header_tree , hf_rsvp_version , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_header_tree , hf_rsvp_flags , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint ( rsvp_header_tree , hf_rsvp_filter [ RSVPF_MSG ] , tvb , offset + 1 , 1 , message_type ) ;
 switch ( RSVPF_MSG + message_type ) {
 case RSVPF_PATH : case RSVPF_RESV : case RSVPF_PATHERR : case RSVPF_RESVERR : case RSVPF_PATHTEAR : case RSVPF_RESVTEAR : case RSVPF_RCONFIRM : case RSVPF_RTEARCONFIRM : case RSVPF_BUNDLE : case RSVPF_ACK : case RSVPF_SREFRESH : case RSVPF_HELLO : case RSVPF_NOTIFY : hidden_item = proto_tree_add_boolean ( rsvp_header_tree , hf_rsvp_filter [ RSVPF_MSG + message_type ] , tvb , offset + 1 , 1 , 1 ) ;
 PROTO_ITEM_SET_HIDDEN ( hidden_item ) ;
 break ;
 }
 cksum = tvb_get_ntohs ( tvb , offset + 2 ) ;
 cksum_item = proto_tree_add_item ( rsvp_header_tree , hf_rsvp_message_checksum , tvb , offset + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_header_tree , hf_rsvp_sending_ttl , tvb , offset + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_header_tree , hf_rsvp_message_length , tvb , offset + 6 , 2 , ENC_BIG_ENDIAN ) ;
 offset = 8 ;
 len = 8 ;
 if ( message_type == RSVP_MSG_BUNDLE ) {
 if ( rsvp_bundle_dissect ) {
 int len2 = 8 ;
 while ( len2 < msg_length ) {
 gint sub_len ;
 tvbuff_t * tvb_sub ;
 sub_len = tvb_get_ntohs ( tvb , len2 + 6 ) ;
 tvb_sub = tvb_new_subset_length ( tvb , len2 , sub_len ) ;
 dissect_rsvp_msg_tree ( tvb_sub , pinfo , rsvp_tree , TREE ( TT_BUNDLE_COMPMSG ) , rsvph , e2ei ) ;
 len2 += sub_len ;
 }
 }
 else {
 proto_tree_add_expert ( rsvp_tree , pinfo , & ei_rsvp_bundle_component_msg , tvb , offset , msg_length - len ) ;
 }
 return ;
 }
 while ( len < msg_length ) {
 guint8 rsvp_class ;
 guint8 type ;
 obj_length = tvb_get_ntohs ( tvb , offset ) ;
 rsvp_class = tvb_get_guint8 ( tvb , offset + 2 ) ;
 type = tvb_get_guint8 ( tvb , offset + 3 ) ;
 ti = proto_tree_add_item ( rsvp_tree , hf_rsvp_filter [ rsvp_class_to_filter_num ( rsvp_class ) ] , tvb , offset , obj_length , ENC_BIG_ENDIAN ) ;
 rsvp_object_tree = proto_item_add_subtree ( ti , TREE ( rsvp_class_to_tree_type ( rsvp_class ) ) ) ;
 len_item = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_length , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 if ( obj_length < 4 ) {
 expert_add_info_format ( pinfo , len_item , & ei_rsvp_invalid_length , "Length: %u (bogus, must be >= 4)" , obj_length ) ;
 break ;
 }
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_OBJECT ] , tvb , offset + 2 , 1 , rsvp_class ) ;
 switch ( rsvp_class ) {
 case RSVP_CLASS_SESSION : dissect_rsvp_session ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type , rsvph ) ;
 break ;
 case RSVP_CLASS_HOP : dissect_rsvp_hop ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_TIME_VALUES : dissect_rsvp_time_values ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_ERROR : dissect_rsvp_error ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_SCOPE : dissect_rsvp_scope ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_STYLE : dissect_rsvp_style ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_CONFIRM : dissect_rsvp_confirm ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_SENDER_TEMPLATE : case RSVP_CLASS_FILTER_SPEC : dissect_rsvp_template_filter ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type , rsvph ) ;
 break ;
 case RSVP_CLASS_SENDER_TSPEC : dissect_rsvp_tspec ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_FLOWSPEC : dissect_rsvp_flowspec ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_ADSPEC : dissect_rsvp_adspec ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_INTEGRITY : have_integrity_object = TRUE ;
 dissect_rsvp_integrity ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_POLICY : dissect_rsvp_policy ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_LABEL_REQUEST : dissect_rsvp_label_request ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_RECOVERY_LABEL : case RSVP_CLASS_UPSTREAM_LABEL : case RSVP_CLASS_SUGGESTED_LABEL : case RSVP_CLASS_LABEL : dissect_rsvp_label ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_LABEL_SET : dissect_rsvp_label_set ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_SESSION_ATTRIBUTE : dissect_rsvp_session_attribute ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_EXPLICIT_ROUTE : dissect_rsvp_explicit_route ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_RECORD_ROUTE : dissect_rsvp_record_route ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_EXCLUDE_ROUTE : dissect_rsvp_exclude_route ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_MESSAGE_ID : dissect_rsvp_message_id ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_MESSAGE_ID_ACK : dissect_rsvp_message_id_ack ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_MESSAGE_ID_LIST : dissect_rsvp_message_id_list ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_HELLO : dissect_rsvp_hello ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_DCLASS : dissect_rsvp_dclass ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_ADMIN_STATUS : dissect_rsvp_admin_status ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_LSP_ATTRIBUTES : case RSVP_CLASS_LSP_REQUIRED_ATTRIBUTES : dissect_rsvp_lsp_attributes ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_ASSOCIATION : dissect_rsvp_association ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_LSP_TUNNEL_IF_ID : dissect_rsvp_lsp_tunnel_if_id ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_NOTIFY_REQUEST : dissect_rsvp_notify_request ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_GENERALIZED_UNI : dissect_rsvp_gen_uni ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type , rsvph ) ;
 break ;
 case RSVP_CLASS_CALL_ID : dissect_rsvp_call_id ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_3GPP2_OBJECT : dissect_rsvp_3gpp_object ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_RESTART_CAP : dissect_rsvp_restart_cap ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_LINK_CAP : dissect_rsvp_link_cap ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_PROTECTION : dissect_rsvp_protection_info ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_FAST_REROUTE : dissect_rsvp_fast_reroute ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_DETOUR : dissect_rsvp_detour ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_DIFFSERV : dissect_rsvp_diffserv ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_CLASSTYPE : dissect_rsvp_diffserv_aware_te ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_VENDOR_PRIVATE_1 : case RSVP_CLASS_VENDOR_PRIVATE_2 : case RSVP_CLASS_VENDOR_PRIVATE_3 : case RSVP_CLASS_VENDOR_PRIVATE_4 : case RSVP_CLASS_VENDOR_PRIVATE_5 : case RSVP_CLASS_VENDOR_PRIVATE_6 : case RSVP_CLASS_VENDOR_PRIVATE_7 : case RSVP_CLASS_VENDOR_PRIVATE_8 : case RSVP_CLASS_VENDOR_PRIVATE_9 : case RSVP_CLASS_VENDOR_PRIVATE_10 : case RSVP_CLASS_VENDOR_PRIVATE_11 : case RSVP_CLASS_VENDOR_PRIVATE_12 : dissect_rsvp_vendor_private_use ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_CALL_ATTRIBUTES : dissect_rsvp_call_attributes ( ti , pinfo , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_JUNIPER_PROPERTIES : dissect_rsvp_juniper ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 case RSVP_CLASS_NULL : default : dissect_rsvp_unknown ( ti , rsvp_object_tree , tvb , offset , obj_length , rsvp_class , type ) ;
 break ;
 }
 offset += obj_length ;
 len += obj_length ;
 }
 if ( ! pinfo -> fragmented && ( ( int ) tvb_captured_length ( tvb ) >= msg_length ) ) {
 SET_CKSUM_VEC_TVB ( cksum_vec [ 0 ] , tvb , 0 , msg_length ) ;
 computed_cksum = in_cksum ( & cksum_vec [ 0 ] , 1 ) ;
 if ( computed_cksum == 0 ) {
 proto_item_append_text ( cksum_item , " [correct]" ) ;
 }
 else if ( cksum == 0 && have_integrity_object ) {
 proto_item_append_text ( cksum_item , " [ignored, integrity object used]" ) ;
 }
 else {
 proto_item_append_text ( cksum_item , " [incorrect, should be 0x%04x]" , in_cksum_shouldbe ( cksum , computed_cksum ) ) ;
 }
 }
 }