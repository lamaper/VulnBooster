static void dtap_mm_loc_upd_acc ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_FALSE ;
 ELEM_MAND_V ( GSM_A_PDU_TYPE_COMMON , DE_LAI , NULL ) ;
 ELEM_OPT_TLV ( 0x17 , GSM_A_PDU_TYPE_COMMON , DE_MID , NULL ) ;
 ELEM_OPT_T ( 0xa1 , GSM_A_PDU_TYPE_DTAP , DE_FOP , NULL ) ;
 ELEM_OPT_T ( 0xa2 , GSM_A_PDU_TYPE_DTAP , DE_CTS_PERM , NULL ) ;
 ELEM_OPT_TLV ( 0x4a , GSM_A_PDU_TYPE_COMMON , DE_PLMN_LIST , " Equivalent" ) ;
 ELEM_OPT_TLV ( 0x34 , GSM_A_PDU_TYPE_DTAP , DE_EMERGENCY_NUM_LIST , NULL ) ;
 ELEM_OPT_TLV ( 0x35 , GSM_A_PDU_TYPE_GM , DE_GPRS_TIMER_3 , " - Per MS T3212" ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }