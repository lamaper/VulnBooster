void proto_register_zbee_zcl_ballast_configuration ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_ballast_configuration_attr_id , {
 "Attribute" , "zbee_zcl_lighting.ballast_configuration.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_ballast_configuration_attr_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ballast_configuration_status , {
 "Status" , "zbee_zcl_lighting.ballast_configuration.attr.status" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ballast_configuration_status_non_operational , {
 "Non-operational" , "zbee_zcl_lighting.ballast_configuration.attr.status.non_operational" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_ballast_configuration_status_non_operational_names ) , ZBEE_ZCL_BALLAST_CONFIGURATION_STATUS_NON_OPERATIONAL , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ballast_configuration_status_lamp_not_in_socket , {
 "Not in Socket" , "zbee_zcl_lighting.ballast_configuration.attr.status.not_in_socket" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_ballast_configuration_status_lamp_not_in_socket_names ) , ZBEE_ZCL_BALLAST_CONFIGURATION_STATUS_LAMP_NOT_IN_SOCKET , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ballast_configuration_lamp_alarm_mode , {
 "Lamp Alarm Mode" , "zbee_zcl_lighting.ballast_configuration.attr.lamp_alarm_mode" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_ballast_configuration_lamp_alarm_mode_lamp_burn_hours , {
 "Lamp Burn Hours" , "zbee_zcl_lighting.ballast_configuration.attr.lamp_alarm_mode.lamp_burn_hours" , FT_BOOLEAN , 8 , NULL , ZBEE_ZCL_BALLAST_CONFIGURATION_LAMP_ALARM_MODE_LAMP_BURN_HOURS , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ZBEE_ZCL_BALLAST_CONFIGURATION_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_ballast_configuration ;
 ett [ 1 ] = & ett_zbee_zcl_ballast_configuration_status ;
 ett [ 2 ] = & ett_zbee_zcl_ballast_configuration_lamp_alarm_mode ;
 proto_zbee_zcl_ballast_configuration = proto_register_protocol ( "ZigBee ZCL Ballast Configuration" , "ZCL Ballast Configuration" , ZBEE_PROTOABBREV_ZCL_BALLAST_CONFIG ) ;
 proto_register_field_array ( proto_zbee_zcl_ballast_configuration , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_BALLAST_CONFIG , dissect_zbee_zcl_ballast_configuration , proto_zbee_zcl_ballast_configuration ) ;
 }