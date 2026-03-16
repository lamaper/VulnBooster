static void dtap_mm_id_resp ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_TRUE ;
 ELEM_MAND_LV ( GSM_A_PDU_TYPE_COMMON , DE_MID , NULL ) ;
 ELEM_OPT_TV_SHORT ( 0xE0 , GSM_A_PDU_TYPE_GM , DE_PTMSI_TYPE , NULL ) ;
 ELEM_OPT_TLV ( 0x1B , GSM_A_PDU_TYPE_GM , DE_RAI_2 , " - Routing area identification" ) ;
 ELEM_OPT_TLV ( 0x19 , GSM_A_PDU_TYPE_GM , DE_P_TMSI_SIG_2 , " - P-TMSI signature" ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }