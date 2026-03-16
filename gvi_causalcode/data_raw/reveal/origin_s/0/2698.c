void proto_register_zbee_zcl_basic ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_basic_attr_id , {
 "Attribute" , "zbee_zcl_general.basic.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_basic_attr_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_pwr_src , {
 "Power Source" , "zbee_zcl_general.basic.attr.pwr_src" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_basic_pwr_src_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_dev_en , {
 "Device Enabled" , "zbee_zcl_general.basic.attr.dev_en" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_basic_dev_en_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_alarm_mask , {
 "Alarm Mask" , "zbee_zcl_general.basic.attr.alarm_mask" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_alarm_mask_gen_hw_fault , {
 "General hardware fault" , "zbee_zcl_general.basic.attr.alarm_mask.gen_hw_fault" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_BASIC_ALARM_GEN_HW_FAULT , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_alarm_mask_gen_sw_fault , {
 "General software fault" , "zbee_zcl_general.basic.attr.alarm_mask.gen_sw_fault" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_BASIC_ALARM_GEN_SW_FAULT , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_alarm_mask_reserved , {
 "Reserved" , "zbee_zcl_general.basic.attr.alarm_mask.reserved" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_BASIC_ALARM_RESERVED , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_disable_local_cfg , {
 "Disable Local Config" , "zbee_zcl_general.basic.attr.dis_loc_cfg" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_disable_local_cfg_reset , {
 "Reset (to factory defaults)" , "zbee_zcl_general.basic.attr.dis_loc_cfg.reset" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_BASIC_DIS_LOC_CFG_RESET , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_disable_local_cfg_device_cfg , {
 "Device configuration" , "zbee_zcl_general.basic.attr.dis_loc_cfg.dev_cfg" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_BASIC_DIS_LOC_CFG_DEV_CFG , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_disable_local_cfg_reserved , {
 "Reserved" , "zbee_zcl_general.basic.attr.dis_loc_cfg.reserved" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_BASIC_DIS_LOC_CFG_RESERVED , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_basic_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_general.basic.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_basic_srv_rx_cmd_names ) , 0x00 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ZBEE_ZCL_BASIC_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_basic ;
 ett [ 1 ] = & ett_zbee_zcl_basic_alarm_mask ;
 ett [ 2 ] = & ett_zbee_zcl_basic_dis_local_cfg ;
 proto_zbee_zcl_basic = proto_register_protocol ( "ZigBee ZCL Basic" , "ZCL Basic" , ZBEE_PROTOABBREV_ZCL_BASIC ) ;
 proto_register_field_array ( proto_zbee_zcl_basic , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_BASIC , dissect_zbee_zcl_basic , proto_zbee_zcl_basic ) ;
 }