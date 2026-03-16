void proto_reg_handoff_zbee_zcl_color_control ( void ) {
 zbee_zcl_init_cluster ( ZBEE_PROTOABBREV_ZCL_COLOR_CONTROL , proto_zbee_zcl_color_control , ett_zbee_zcl_color_control , ZBEE_ZCL_CID_COLOR_CONTROL , ZBEE_MFG_CODE_NONE , hf_zbee_zcl_color_control_attr_id , hf_zbee_zcl_color_control_srv_rx_cmd_id , - 1 , ( zbee_zcl_fn_attr_data ) dissect_zcl_color_control_attr_data ) ;
 }