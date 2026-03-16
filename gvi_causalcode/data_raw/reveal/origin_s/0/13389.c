void proto_reg_handoff_zbee_zcl_appl_ctrl ( void ) {
 dissector_handle_t appl_ctrl_handle ;
 appl_ctrl_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_APPLCTRL ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_APPLIANCE_CONTROL , appl_ctrl_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_appl_ctrl , ett_zbee_zcl_appl_ctrl , ZBEE_ZCL_CID_APPLIANCE_CONTROL , hf_zbee_zcl_appl_ctrl_attr_id , hf_zbee_zcl_appl_ctrl_srv_rx_cmd_id , hf_zbee_zcl_appl_ctrl_srv_tx_cmd_id , ( zbee_zcl_fn_attr_data ) dissect_zcl_appl_ctrl_attr_data ) ;
 }