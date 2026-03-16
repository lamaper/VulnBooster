void proto_register_zbee_zcl_power_config ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_power_config_attr_id , {
 "Attribute" , "zbee_zcl_general.power_config.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_power_config_attr_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_batt_type , {
 "Battery Type" , "zbee_zcl_general.power_config.attr.batt_type" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_power_config_batt_type_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_mains_alarm_mask , {
 "Mains Alarm Mask" , "zbee_zcl_general.power_config.attr.mains_alarm_mask" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_mains_alarm_mask_low , {
 "Mains Voltage too low" , "zbee_zcl_general.power_config.attr.mains_alarm_mask.mains_too_low" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_POWER_CONF_MAINS_ALARM_LOW , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_mains_alarm_mask_high , {
 "Mains Voltage too high" , "zbee_zcl_general.power_config.attr.mains_alarm_mask.mains_too_high" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_POWER_CONF_MAINS_ALARM_HIGH , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_mains_alarm_mask_reserved , {
 "Reserved" , "zbee_zcl_general.power_config.attr.mains_alarm_mask.reserved" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_POWER_CONF_MAINS_ALARM_RESERVED , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_batt_alarm_mask , {
 "Battery Alarm Mask" , "zbee_zcl_general.power_config.attr.batt_alarm_mask" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_batt_alarm_mask_low , {
 "Battery Voltage too low" , "zbee_zcl_general.power_config.batt_attr.alarm_mask.batt_too_low" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_POWER_CONF_BATTERY_ALARM_LOW , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_batt_alarm_mask_reserved , {
 "Reserved" , "zbee_zcl_general.power_config.attr.batt_alarm_mask.reserved" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_POWER_CONF_BATTERY_ALARM_RESERVED , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_mains_voltage , {
 "Measured Mains Voltage" , "zbee_zcl_general.power_config.attr.mains_voltage" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_power_conf_voltage ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_mains_frequency , {
 "Measured Mains Frequency" , "zbee_zcl_general.power_config.attr.mains_frequency" , FT_UINT8 , BASE_CUSTOM , CF_FUNC ( decode_power_conf_frequency ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_mains_voltage_min_thr , {
 "Mains Voltage Minimum Threshold" , "zbee_zcl_general.power_config.attr.mains_volt_min" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_power_conf_voltage ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_mains_voltage_max_thr , {
 "Mains Voltage Maximum Threshold" , "zbee_zcl_general.power_config.attr.mains_volt_max" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_power_conf_voltage ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_batt_voltage , {
 "Measured Battey Voltage" , "zbee_zcl_general.power_config.attr.batt_voltage" , FT_UINT8 , BASE_CUSTOM , CF_FUNC ( decode_power_conf_voltage ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_batt_ah_rating , {
 "Battery Capacity" , "zbee_zcl_general.power_config.attr.batt_AHr" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_power_conf_batt_AHr ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_batt_rated_voltage , {
 "Battery Rated Voltage" , "zbee_zcl_general.power_config.attr.batt_rated_voltage" , FT_UINT8 , BASE_CUSTOM , CF_FUNC ( decode_power_conf_voltage ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_batt_voltage_min_thr , {
 "Battery Voltage Minimum Threshold" , "zbee_zcl_general.power_config.attr.batt_voltage_min_thr" , FT_UINT8 , BASE_CUSTOM , CF_FUNC ( decode_power_conf_voltage ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_power_config_mains_voltage_dwell_tp , {
 "Mains Voltage Dwell Trip Point" , "zbee_zcl_general.power_config.attr.mains_dwell_tp" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_zbee_zcl_power_config , & ett_zbee_zcl_power_config_mains_alarm_mask , & ett_zbee_zcl_power_config_batt_alarm_mask }
 ;
 proto_zbee_zcl_power_config = proto_register_protocol ( "ZigBee ZCL Power Configuration" , "ZCL Power Configuration" , ZBEE_PROTOABBREV_ZCL_POWER_CONFIG ) ;
 proto_register_field_array ( proto_zbee_zcl_power_config , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_POWER_CONFIG , dissect_zbee_zcl_power_config , proto_zbee_zcl_power_config ) ;
 }