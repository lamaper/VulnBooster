static void dtap_tp_epc_test_loop_mode_c_mbms_packet_counter_response ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_len = len ;
 curr_offset = offset ;
 ELEM_MAND_V ( GSM_A_PDU_TYPE_DTAP , DE_TP_EPC_MBMS_PACKET_COUNTER_VALUE , NULL ) ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }