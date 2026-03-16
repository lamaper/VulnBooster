static void dtap_cc_status ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_FALSE ;
 ELEM_MAND_LV ( GSM_A_PDU_TYPE_DTAP , DE_CAUSE , NULL ) ;
 ELEM_MAND_V ( GSM_A_PDU_TYPE_DTAP , DE_CALL_STATE , NULL ) ;
 ELEM_OPT_TLV ( 0x24 , GSM_A_PDU_TYPE_DTAP , DE_AUX_STATES , NULL ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }