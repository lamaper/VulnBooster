void proto_reg_handoff_zbee_zcl_appl_evtalt ( void ) {
 dissector_handle_t appl_evtalt_handle ;
 appl_evtalt_handle = find_dissector ( ZBEE_PROTOABBREV_ZCL_APPLEVTALT ) ;
 dissector_add_uint ( "zbee.zcl.cluster" , ZBEE_ZCL_CID_APPLIANCE_EVENTS_AND_ALERT , appl_evtalt_handle ) ;
 zbee_zcl_init_cluster ( proto_zbee_zcl_appl_evtalt , ett_zbee_zcl_appl_evtalt , ZBEE_ZCL_CID_APPLIANCE_EVENTS_AND_ALERT , - 1 , hf_zbee_zcl_appl_evtalt_srv_rx_cmd_id , hf_zbee_zcl_appl_evtalt_srv_tx_cmd_id , NULL ) ;
 }