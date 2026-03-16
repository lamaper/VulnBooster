void proto_reg_handoff_zbee_zcl_appl_stats ( void ) {
 dissector_handle_t appl_stats_handle ;
 appl_stats_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_APPLSTATS ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_APPLIANCE_STATISTICS , appl_stats_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_appl_stats , ett_zbee_zcl_appl_stats , ZBEE_ZCL_CID_APPLIANCE_STATISTICS , hf_zbee_zcl_appl_stats_attr_id , hf_zbee_zcl_appl_stats_srv_rx_cmd_id , hf_zbee_zcl_appl_stats_srv_tx_cmd_id , NULL ) ;
 }