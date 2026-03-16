static void dtap_tp_epc_close_ue_test_loop ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len ) {
 guint32 curr_offset ;
 guint32 consumed ;
 guint curr_len ;
 curr_len = len ;
 curr_offset = offset ;
 ELEM_MAND_V ( GSM_A_PDU_TYPE_DTAP , DE_TP_EPC_UE_TEST_LOOP_MODE , NULL ) ;
 switch ( epc_test_loop_mode ) {
 case 0 : ELEM_MAND_LV ( GSM_A_PDU_TYPE_DTAP , DE_TP_EPC_UE_TL_A_LB_SETUP , NULL ) ;
 break ;
 case 1 : ELEM_MAND_V ( GSM_A_PDU_TYPE_DTAP , DE_TP_EPC_UE_TL_B_LB_SETUP , NULL ) ;
 break ;
 case 2 : ELEM_MAND_V ( GSM_A_PDU_TYPE_DTAP , DE_TP_EPC_UE_TL_C_SETUP , NULL ) ;
 break ;
 default : break ;
 }
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 }