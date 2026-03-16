static void dtap_cc_disconnect ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_TRUE ;
 ELEM_MAND_LV ( GSM_A_PDU_TYPE_DTAP , DE_CAUSE , NULL ) ;
 ELEM_OPT_TLV ( 0x1c , GSM_A_PDU_TYPE_DTAP , DE_FACILITY , NULL ) ;
 ELEM_OPT_TLV ( 0x1e , GSM_A_PDU_TYPE_DTAP , DE_PROG_IND , NULL ) ;
 ELEM_OPT_TLV ( 0x7e , GSM_A_PDU_TYPE_DTAP , DE_USER_USER , NULL ) ;
 ELEM_OPT_TLV ( 0x7b , GSM_A_PDU_TYPE_DTAP , DE_ALLOWED_ACTIONS , NULL ) ;
 ELEM_OPT_TLV ( 0x7f , GSM_A_PDU_TYPE_DTAP , DE_SS_VER_IND , NULL ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }