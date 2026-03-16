void proto_reg_handoff_zbee_zcl_scenes ( void ) {
 dissector_handle_t scenes_handle ;
 scenes_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_SCENES ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_SCENES , scenes_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_scenes , ett_zbee_zcl_scenes , ZBEE_ZCL_CID_SCENES , hf_zbee_zcl_scenes_attr_id , hf_zbee_zcl_scenes_srv_rx_cmd_id , hf_zbee_zcl_scenes_srv_tx_cmd_id , ( zbee_zcl_fn_attr_data ) dissect_zcl_scenes_attr_data ) ;
 }