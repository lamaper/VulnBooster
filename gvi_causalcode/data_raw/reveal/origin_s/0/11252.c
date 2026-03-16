void proto_reg_handoff_zbee_zcl_part ( void ) {
 dissector_handle_t part_handle ;
 part_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_PART ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_PARTITION , part_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_part , ett_zbee_zcl_part , ZBEE_ZCL_CID_PARTITION , hf_zbee_zcl_part_attr_id , hf_zbee_zcl_part_srv_rx_cmd_id , hf_zbee_zcl_part_srv_tx_cmd_id , NULL ) ;
 }