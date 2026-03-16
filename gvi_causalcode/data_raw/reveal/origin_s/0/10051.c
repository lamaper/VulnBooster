void proto_register_zbee_zcl_on_off ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_on_off_attr_id , {
 "Attribute" , "zbee_zcl_general.onoff.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_on_off_attr_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_on_off_attr_onoff , {
 "Data Value" , "zbee_zcl_general.onoff.attr.onoff" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_on_off_onoff_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_on_off_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_general.onoff.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_on_off_srv_rx_cmd_names ) , 0x00 , NULL , HFILL }
 }
 }
 ;
 proto_zbee_zcl_on_off = proto_register_protocol ( "ZigBee ZCL OnOff" , "ZCL OnOff" , ZBEE_PROTOABBREV_ZCL_ONOFF ) ;
 proto_register_field_array ( proto_zbee_zcl_on_off , hf , array_length ( hf ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_ONOFF , dissect_zbee_zcl_on_off , proto_zbee_zcl_on_off ) ;
 }