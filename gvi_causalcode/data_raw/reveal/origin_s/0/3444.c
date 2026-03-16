static void dtap_cc_start_dtmf ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_TRUE ;
 ELEM_MAND_TV ( 0x2c , GSM_A_PDU_TYPE_DTAP , DE_KEYPAD_FACILITY , NULL , ei_gsm_a_dtap_missing_mandatory_element ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }