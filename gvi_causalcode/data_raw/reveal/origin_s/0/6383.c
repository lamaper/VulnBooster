void dtap_mm_mm_info ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_offset = offset ;
 curr_len = len ;
 is_uplink = IS_UPLINK_TRUE ;
 ELEM_OPT_TLV ( 0x43 , GSM_A_PDU_TYPE_DTAP , DE_NETWORK_NAME , " - Full Name" ) ;
 ELEM_OPT_TLV ( 0x45 , GSM_A_PDU_TYPE_DTAP , DE_NETWORK_NAME , " - Short Name" ) ;
 ELEM_OPT_TV ( 0x46 , GSM_A_PDU_TYPE_DTAP , DE_TIME_ZONE , " - Local" ) ;
 ELEM_OPT_TV ( 0x47 , GSM_A_PDU_TYPE_DTAP , DE_TIME_ZONE_TIME , " - Universal Time and Local Time Zone" ) ;
 ELEM_OPT_TLV ( 0x48 , GSM_A_PDU_TYPE_DTAP , DE_LSA_ID , NULL ) ;
 ELEM_OPT_TLV ( 0x49 , GSM_A_PDU_TYPE_DTAP , DE_DAY_SAVING_TIME , NULL ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }