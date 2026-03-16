static void dtap_cc_call_proceed ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_FALSE ;
 ELEM_OPT_TV_SHORT ( 0xd0 , GSM_A_PDU_TYPE_DTAP , DE_REPEAT_IND , " BC repeat indicator" ) ;
 ELEM_OPT_TLV ( 0x04 , GSM_A_PDU_TYPE_DTAP , DE_BEARER_CAP , " 1" ) ;
 ELEM_OPT_TLV ( 0x04 , GSM_A_PDU_TYPE_DTAP , DE_BEARER_CAP , " 2" ) ;
 ELEM_OPT_TLV ( 0x1c , GSM_A_PDU_TYPE_DTAP , DE_FACILITY , NULL ) ;
 ELEM_OPT_TLV ( 0x1e , GSM_A_PDU_TYPE_DTAP , DE_PROG_IND , NULL ) ;
 ELEM_OPT_TV_SHORT ( 0x80 , GSM_A_PDU_TYPE_COMMON , DE_PRIO , NULL ) ;
 ELEM_OPT_TLV ( 0x2f , GSM_A_PDU_TYPE_DTAP , DE_NET_CC_CAP , NULL ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }