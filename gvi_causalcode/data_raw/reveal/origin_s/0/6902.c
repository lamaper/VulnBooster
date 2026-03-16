const char * get_gsm_a_msg_string ( int pdu_type , int idx ) {
 const char * msg_string = NULL ;
 switch ( pdu_type ) {
 case GSM_A_PDU_TYPE_BSSMAP : msg_string = val_to_str_ext ( idx , & gsm_bssmap_elem_strings_ext , "GSM_A_PDU_TYPE_BSSMAP (%u)" ) ;
 break ;
 case GSM_A_PDU_TYPE_DTAP : msg_string = val_to_str_ext ( idx , & gsm_dtap_elem_strings_ext , "GSM_A_PDU_TYPE_DTAP (%u)" ) ;
 break ;
 case GSM_A_PDU_TYPE_RP : msg_string = val_to_str_ext ( idx , & gsm_rp_elem_strings_ext , "GSM_A_PDU_TYPE_RP (%u)" ) ;
 break ;
 case GSM_A_PDU_TYPE_RR : msg_string = val_to_str_ext ( idx , & gsm_rr_elem_strings_ext , "GSM_A_PDU_TYPE_RR (%u)" ) ;
 break ;
 case GSM_A_PDU_TYPE_COMMON : msg_string = val_to_str_ext ( idx , & gsm_common_elem_strings_ext , "GSM_A_PDU_TYPE_COMMON (%u)" ) ;
 break ;
 case GSM_A_PDU_TYPE_GM : msg_string = val_to_str_ext ( idx , & gsm_gm_elem_strings_ext , "GSM_A_PDU_TYPE_GM (%u)" ) ;
 break ;
 case GSM_A_PDU_TYPE_BSSLAP : msg_string = val_to_str_ext ( idx , & gsm_bsslap_elem_strings_ext , "GSM_A_PDU_TYPE_BSSLAP (%u)" ) ;
 break ;
 case GSM_PDU_TYPE_BSSMAP_LE : msg_string = val_to_str_ext ( idx , & gsm_bssmap_le_elem_strings_ext , "GSM_PDU_TYPE_BSSMAP_LE (%u)" ) ;
 break ;
 case NAS_PDU_TYPE_COMMON : msg_string = val_to_str_ext ( idx , & nas_eps_common_elem_strings_ext , "NAS_PDU_TYPE_COMMON (%u)" ) ;
 break ;
 case NAS_PDU_TYPE_EMM : msg_string = val_to_str_ext ( idx , & nas_emm_elem_strings_ext , "NAS_PDU_TYPE_EMM (%u)" ) ;
 break ;
 case NAS_PDU_TYPE_ESM : msg_string = val_to_str_ext ( idx , & nas_esm_elem_strings_ext , "NAS_PDU_TYPE_ESM (%u)" ) ;
 break ;
 case SGSAP_PDU_TYPE : msg_string = val_to_str_ext ( idx , & sgsap_elem_strings_ext , "SGSAP_PDU_TYPE (%u)" ) ;
 break ;
 case BSSGP_PDU_TYPE : msg_string = val_to_str_ext ( idx , & bssgp_elem_strings_ext , "BSSGP_PDU_TYPE (%u)" ) ;
 break ;
 case GMR1_IE_COMMON : msg_string = val_to_str_ext ( idx , & gmr1_ie_common_strings_ext , "GMR1_IE_COMMON (%u)" ) ;
 break ;
 case GMR1_IE_RR : msg_string = val_to_str_ext ( idx , & gmr1_ie_rr_strings_ext , "GMR1_IE_RR (%u)" ) ;
 break ;
 default : DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }
 return msg_string ;
 }