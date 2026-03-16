static int dissect_zbee_zcl_appl_ctrl ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_tree * payload_tree ;
 zbee_zcl_packet * zcl ;
 guint offset = 0 ;
 guint8 cmd_id ;
 gint rem_len ;
 if ( data == NULL ) return 0 ;
 zcl = ( zbee_zcl_packet * ) data ;
 cmd_id = zcl -> cmd_id ;
 if ( zcl -> direction == ZBEE_ZCL_FCF_TO_SERVER ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_appl_ctrl_srv_rx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_ctrl_srv_rx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_appl_ctrl , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_APPL_CTRL_EXECUTION_CMD : dissect_zcl_appl_ctrl_exec_cmd ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_APPL_CTRL_SIGNAL_STATE : case ZBEE_ZCL_CMD_ID_APPL_CTRL_OVERLOAD_PAUSE_RESUME : case ZBEE_ZCL_CMD_ID_APPL_CTRL_OVERLOAD_PAUSE : break ;
 case ZBEE_ZCL_CMD_ID_APPL_CTRL_WRITE_FUNCS : dissect_zcl_appl_ctrl_wr_funcs ( tvb , payload_tree , & offset ) ;
 break ;
 case ZBEE_ZCL_CMD_ID_APPL_CTRL_OVERLOAD_WARNING : dissect_zcl_appl_ctrl_ovrl_warning ( tvb , payload_tree , & offset ) ;
 break ;
 default : break ;
 }
 }
 }
 else {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s, Seq: %u" , val_to_str_const ( cmd_id , zbee_zcl_appl_ctrl_srv_tx_cmd_names , "Unknown Command" ) , zcl -> tran_seqno ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_appl_ctrl_srv_tx_cmd_id , tvb , offset , 1 , cmd_id ) ;
 rem_len = tvb_reported_length_remaining ( tvb , ++ offset ) ;
 if ( rem_len > 0 ) {
 payload_tree = proto_tree_add_subtree ( tree , tvb , offset , rem_len , ett_zbee_zcl_appl_ctrl , NULL , "Payload" ) ;
 switch ( cmd_id ) {
 case ZBEE_ZCL_CMD_ID_APPL_CTRL_SIGNAL_STATE_RSP : case ZBEE_ZCL_CMD_ID_APPL_CTRL_SIGNAL_STATE_NOTIF : dissect_zcl_appl_ctrl_signal_state_rsp ( tvb , payload_tree , & offset ) ;
 break ;
 default : break ;
 }
 }
 }
 return tvb_captured_length ( tvb ) ;
 }