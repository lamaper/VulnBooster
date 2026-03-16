static void dtap_bcc_status ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 ELEM_MAND_LV ( GSM_A_PDU_TYPE_DTAP , DE_BCC_CAUSE , NULL ) ;
 ELEM_OPT_TV_SHORT ( 0xa0 , GSM_A_PDU_TYPE_DTAP , DE_BCC_CALL_STATE , NULL ) ;
 ELEM_OPT_TV_SHORT ( 0xb0 , GSM_A_PDU_TYPE_DTAP , DE_BCC_STATE_ATTR , NULL ) ;
 }