void proto_reg_handoff_zbee_zcl_ota ( void ) {
 dissector_handle_t ota_handle ;
 ota_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_OTA ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_OTA_UPGRADE , ota_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_ota , ett_zbee_zcl_ota , ZBEE_ZCL_CID_OTA_UPGRADE , hf_zbee_zcl_ota_attr_id , hf_zbee_zcl_ota_srv_rx_cmd_id , hf_zbee_zcl_ota_srv_tx_cmd_id , ( zbee_zcl_fn_attr_data ) dissect_zcl_ota_attr_data ) ;
 }