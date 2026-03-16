void proto_reg_handoff_zbee_zcl_poll_ctrl ( void ) {
 dissector_handle_t poll_handle ;
 poll_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_POLL ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_POLL_CONTROL , poll_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_poll_ctrl , ett_zbee_zcl_poll_ctrl , ZBEE_ZCL_CID_POLL_CONTROL , hf_zbee_zcl_poll_ctrl_attr_id , hf_zbee_zcl_poll_ctrl_srv_rx_cmd_id , hf_zbee_zcl_poll_ctrl_srv_tx_cmd_id , ( zbee_zcl_fn_attr_data ) dissect_zcl_poll_ctrl_attr_data ) ;
 }