void proto_reg_handoff_zbee_zcl_basic ( void ) {
 dissector_handle_t basic_handle ;
 basic_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_BASIC ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_BASIC , basic_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_basic , ett_zbee_zcl_basic , ZBEE_ZCL_CID_BASIC , hf_zbee_zcl_basic_attr_id , hf_zbee_zcl_basic_srv_rx_cmd_id , - 1 , ( zbee_zcl_fn_attr_data ) dissect_zcl_basic_attr_data ) ;
 }