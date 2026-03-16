void proto_register_zbee_zcl_identify ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_identify_attr_id , {
 "Attribute" , "zbee_zcl_general.identify.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_identify_attr_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_identify_identify_time , {
 "Identify Time" , "zbee_zcl_general.identify.attr.identify_time" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_seconds ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_identify_identify_timeout , {
 "Identify Timeout" , "zbee_zcl_general.identify.identify_timeout" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_seconds ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_identify_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_general.identify.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_identify_srv_rx_cmd_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_identify_srv_tx_cmd_id , {
 "Command" , "zbee_zcl_general.identify.cmd.srv_tx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_identify_srv_tx_cmd_names ) , 0x00 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ZBEE_ZCL_IDENTIFY_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_identify ;
 proto_zbee_zcl_identify = proto_register_protocol ( "ZigBee ZCL Identify" , "ZCL Identify" , ZBEE_PROTOABBREV_ZCL_IDENTIFY ) ;
 proto_register_field_array ( proto_zbee_zcl_identify , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_IDENTIFY , dissect_zbee_zcl_identify , proto_zbee_zcl_identify ) ;
 }