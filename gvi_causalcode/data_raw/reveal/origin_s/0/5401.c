void proto_reg_handoff_zbee_zcl_power_config ( void ) {
 dissector_handle_t handle ;
 handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_POWER_CONFIG ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_POWER_CONFIG , handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_power_config , ett_zbee_zcl_power_config , ZBEE_ZCL_CID_POWER_CONFIG , hf_zbee_zcl_power_config_attr_id , - 1 , - 1 , ( zbee_zcl_fn_attr_data ) dissect_zcl_power_config_attr_data ) ;
 }