static void dtap_mm_cm_srvc_rej ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_FALSE ;
 ELEM_MAND_V ( GSM_A_PDU_TYPE_DTAP , DE_REJ_CAUSE , NULL ) ;
 ELEM_OPT_TLV ( 0x36 , GSM_A_PDU_TYPE_DTAP , DE_MM_TIMER , " - T3246 value" ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }