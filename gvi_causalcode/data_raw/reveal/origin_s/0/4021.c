static void dtap_cc_call_conf ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_TRUE ;
 ELEM_OPT_TV_SHORT ( 0xd0 , GSM_A_PDU_TYPE_DTAP , DE_REPEAT_IND , " BC repeat indicator" ) ;
 ELEM_OPT_TLV ( 0x04 , GSM_A_PDU_TYPE_DTAP , DE_BEARER_CAP , " 1" ) ;
 ELEM_OPT_TLV ( 0x04 , GSM_A_PDU_TYPE_DTAP , DE_BEARER_CAP , " 2" ) ;
 ELEM_OPT_TLV ( 0x08 , GSM_A_PDU_TYPE_DTAP , DE_CAUSE , NULL ) ;
 ELEM_OPT_TLV ( 0x15 , GSM_A_PDU_TYPE_DTAP , DE_CC_CAP , NULL ) ;
 ELEM_OPT_TLV ( 0x2d , GSM_A_PDU_TYPE_DTAP , DE_SI , NULL ) ;
 ELEM_OPT_TLV ( 0x40 , GSM_A_PDU_TYPE_DTAP , DE_SUP_CODEC_LIST , NULL ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }