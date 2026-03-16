static void dtap_mm_auth_fail ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_TRUE ;
 ELEM_MAND_V ( GSM_A_PDU_TYPE_DTAP , DE_REJ_CAUSE , NULL ) ;
 ELEM_OPT_TLV ( 0x22 , GSM_A_PDU_TYPE_DTAP , DE_AUTH_FAIL_PARAM , NULL ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }