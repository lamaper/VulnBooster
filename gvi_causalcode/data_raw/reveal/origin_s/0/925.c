void proto_reg_handoff_zbee_zcl_identify ( void ) {
 dissector_handle_t identify_handle ;
 identify_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_IDENTIFY ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_IDENTIFY , identify_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_identify , ett_zbee_zcl_identify , ZBEE_ZCL_CID_IDENTIFY , hf_zbee_zcl_identify_attr_id , hf_zbee_zcl_identify_srv_rx_cmd_id , hf_zbee_zcl_identify_srv_tx_cmd_id , ( zbee_zcl_fn_attr_data ) dissect_zcl_identify_attr_data ) ;
 }