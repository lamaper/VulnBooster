void proto_reg_handoff_zbee_zcl_groups ( void ) {
 dissector_handle_t groups_handle ;
 groups_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_GROUPS ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_GROUPS , groups_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_groups , ett_zbee_zcl_groups , ZBEE_ZCL_CID_GROUPS , hf_zbee_zcl_groups_attr_id , hf_zbee_zcl_groups_srv_rx_cmd_id , hf_zbee_zcl_groups_srv_tx_cmd_id , ( zbee_zcl_fn_attr_data ) dissect_zcl_groups_attr_data ) ;
 }