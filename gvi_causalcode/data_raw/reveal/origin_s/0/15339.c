static int get_hf_elem_id ( int pdu_type ) {
 int hf_elem_id = 0 ;
 switch ( pdu_type ) {
 case GSM_A_PDU_TYPE_BSSMAP : hf_elem_id = hf_gsm_a_bssmap_elem_id ;
 break ;
 case GSM_A_PDU_TYPE_DTAP : hf_elem_id = hf_gsm_a_dtap_elem_id ;
 break ;
 case GSM_A_PDU_TYPE_RP : hf_elem_id = hf_gsm_a_rp_elem_id ;
 break ;
 case GSM_A_PDU_TYPE_RR : hf_elem_id = hf_gsm_a_rr_elem_id ;
 break ;
 case GSM_A_PDU_TYPE_COMMON : hf_elem_id = hf_gsm_a_common_elem_id ;
 break ;
 case GSM_A_PDU_TYPE_GM : hf_elem_id = hf_gsm_a_gm_elem_id ;
 break ;
 case GSM_A_PDU_TYPE_BSSLAP : hf_elem_id = hf_gsm_a_bsslap_elem_id ;
 break ;
 case GSM_PDU_TYPE_BSSMAP_LE : hf_elem_id = hf_gsm_bssmap_le_elem_id ;
 break ;
 case NAS_PDU_TYPE_COMMON : hf_elem_id = hf_nas_eps_common_elem_id ;
 break ;
 case NAS_PDU_TYPE_EMM : hf_elem_id = hf_nas_eps_emm_elem_id ;
 break ;
 case NAS_PDU_TYPE_ESM : hf_elem_id = hf_nas_eps_esm_elem_id ;
 break ;
 case SGSAP_PDU_TYPE : hf_elem_id = hf_sgsap_elem_id ;
 break ;
 case BSSGP_PDU_TYPE : hf_elem_id = hf_bssgp_elem_id ;
 break ;
 case GMR1_IE_COMMON : case GMR1_IE_RR : hf_elem_id = hf_gmr1_elem_id ;
 break ;
 default : DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }
 return hf_elem_id ;
 }