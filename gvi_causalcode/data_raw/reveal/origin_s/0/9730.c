static void dtap_cc_modify_complete ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_TRUE ;
 ELEM_MAND_LV ( GSM_A_PDU_TYPE_DTAP , DE_BEARER_CAP , NULL ) ;
 ELEM_OPT_TLV ( 0x7c , GSM_A_PDU_TYPE_DTAP , DE_LLC , NULL ) ;
 ELEM_OPT_TLV ( 0x7d , GSM_A_PDU_TYPE_DTAP , DE_HLC , NULL ) ;
 ELEM_OPT_T ( 0xa3 , GSM_A_PDU_TYPE_DTAP , DE_REV_CALL_SETUP_DIR , NULL ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }