void proto_reg_handoff_zbee_zcl_on_off ( void ) {
 dissector_handle_t on_off_handle ;
 on_off_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_ONOFF ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_ON_OFF , on_off_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_on_off , ett_zbee_zcl_on_off , ZBEE_ZCL_CID_ON_OFF , hf_zbee_zcl_on_off_attr_id , hf_zbee_zcl_on_off_srv_rx_cmd_id , - 1 , ( zbee_zcl_fn_attr_data ) dissect_zcl_on_off_attr_data ) ;
 }