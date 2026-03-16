void proto_reg_handoff_zbee_zcl_pwr_prof ( void ) {
 dissector_handle_t pwr_prof_handle ;
 pwr_prof_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_PWRPROF ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_POWER_PROFILE , pwr_prof_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_pwr_prof , ett_zbee_zcl_pwr_prof , ZBEE_ZCL_CID_POWER_PROFILE , hf_zbee_zcl_pwr_prof_attr_id , hf_zbee_zcl_pwr_prof_srv_rx_cmd_id , hf_zbee_zcl_pwr_prof_srv_tx_cmd_id , ( zbee_zcl_fn_attr_data ) dissect_zcl_pwr_prof_attr_data ) ;
 }