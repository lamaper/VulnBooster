void proto_register_zbee_zcl_color_control ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_color_control_attr_id , {
 "Attribute" , "zbee_zcl_lighting.color_control.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_color_control_attr_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_current_hue , {
 "Hue" , "zbee_zcl_lighting.color_control.attr.current_hue" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_current_saturation , {
 "Saturation" , "zbee_zcl_lighting.color_control.attr.current_satuaration" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_remaining_time , {
 "Time" , "zbee_zcl_lighting.color_control.attr.remaining_time" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_100ms ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.color_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.color_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_drift_compensation , {
 "Drift Compensation" , "zbee_zcl_lighting.color_control.attr.drift_compensation" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_color_control_drift_compensation_values ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_temperature , {
 "Color Temperature" , "zbee_zcl_lighting.color_control.attr.color_temperature" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_temperature ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_mode , {
 "Color Mode" , "zbee_zcl_lighting.color_control.attr.color_mode" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_color_control_color_mode_values ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_nr_of_primaries , {
 "Number" , "zbee_zcl_lighting.color_control.attr.nr_of_primaries" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_1_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.primary_1_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_1_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.primary_1_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_1_intensity , {
 "Intensity" , "zbee_zcl_lighting.color_control.attr.primary_1_intensity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_2_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.primary_2_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_2_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.primary_2_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_2_intensity , {
 "Intensity" , "zbee_zcl_lighting.color_control.attr.primary_2_intensity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_3_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.primary_3_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_3_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.primary_3_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_3_intensity , {
 "Intensity" , "zbee_zcl_lighting.color_control.attr.primary_3_intensity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_4_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.primary_4_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_4_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.primary_4_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_4_intensity , {
 "Intensity" , "zbee_zcl_lighting.color_control.attr.primary_4_intensity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_5_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.primary_5_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_5_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.primary_5_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_5_intensity , {
 "Intensity" , "zbee_zcl_lighting.color_control.attr.primary_5_intensity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_6_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.primary_6_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_6_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.primary_6_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_primary_6_intensity , {
 "Intensity" , "zbee_zcl_lighting.color_control.attr.primary_6_intensity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_white_point_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.white_point_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_white_point_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.white_point_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_red_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.red_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_red_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.red_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_red_intensity , {
 "Intensity" , "zbee_zcl_lighting.color_control.attr.red_intensity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_green_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.green_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_green_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.green_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_green_intensity , {
 "Intensity" , "zbee_zcl_lighting.color_control.attr.green_intensity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_blue_x , {
 "X" , "zbee_zcl_lighting.color_control.attr.blue_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_blue_y , {
 "Y" , "zbee_zcl_lighting.color_control.attr.blue_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_blue_intensity , {
 "Intensity" , "zbee_zcl_lighting.color_control.attr.blue_intensity" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_enhanced_current_hue , {
 "Enhanced Hue" , "zbee_zcl_lighting.color_control.attr.enhanced_current_hue" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_enhanced_color_mode , {
 "Enhanced Color Mode" , "zbee_zcl_lighting.color_control.attr.enhanced_color_mode" , FT_UINT8 , BASE_DEC , VALS ( zbee_zcl_color_control_color_mode_values ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_loop_active , {
 "Active" , "zbee_zcl_lighting.color_control.attr.color_loop_active" , FT_BOOLEAN , 8 , TFS ( & tfs_true_false ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_loop_direction , {
 "Direction" , "zbee_zcl_lighting.color_control.attr.color_loop_direction" , FT_UINT8 , BASE_DEC , VALS ( zbee_zcl_color_control_color_loop_direction_values ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_loop_time , {
 "Time" , "zbee_zcl_lighting.color_control.attr.color_loop_time" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_seconds ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_loop_start_enhanced_hue , {
 "Enhanced Hue" , "zbee_zcl_lighting.color_control.attr.color_loop_start_enhanced_hue" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_loop_stored_enhanced_hue , {
 "Enhanced Hue" , "zbee_zcl_lighting.color_control.attr.color_loop_stored_enhanced_hue" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_capabilities , {
 "Capabilities" , "zbee_zcl_lighting.color_control.attr.color_capabilities" , FT_UINT16 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_capabilities_hs , {
 "Support Hue and Saturation" , "zbee_zcl_lighting.color_control.attr.color_capabilities.hue_saturation" , FT_UINT16 , BASE_DEC , NULL , ZBEE_ZCL_COLOR_CAPABILITIES_SUPPORT_HS_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_capabilities_ehs , {
 "Support Enhanced Hue and Saturation" , "zbee_zcl_lighting.color_control.attr.color_capabilities.enhanced_hue_saturation" , FT_UINT16 , BASE_DEC , NULL , ZBEE_ZCL_COLOR_CAPABILITIES_SUPPORT_EHS_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_capabilities_loop , {
 "Support Color Loop" , "zbee_zcl_lighting.color_control.attr.color_capabilities.color_loop" , FT_UINT16 , BASE_DEC , NULL , ZBEE_ZCL_COLOR_CAPABILITIES_SUPPORT_LOOP_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_capabilities_xy , {
 "Support Color XY" , "zbee_zcl_lighting.color_control.attr.color_capabilities.color_xy" , FT_UINT16 , BASE_DEC , NULL , ZBEE_ZCL_COLOR_CAPABILITIES_SUPPORT_XY_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_capabilities_ct , {
 "Support Color Temperature" , "zbee_zcl_lighting.color_control.attr.color_capabilities.color_temperature" , FT_UINT16 , BASE_DEC , NULL , ZBEE_ZCL_COLOR_CAPABILITIES_SUPPORT_CT_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_temperature_phys_min , {
 "Color Temperature" , "zbee_zcl_lighting.color_control.attr.color_temperature_physical_min" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_temperature ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_attr_color_temperature_phys_max , {
 "Color Temperature" , "zbee_zcl_lighting.color_control.attr.color_temperature_physical_max" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_temperature ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_hue , {
 "Hue" , "zbee_zcl_lighting.color_control.hue" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_direction , {
 "Direction" , "zbee_zcl_lighting.color_control.direction" , FT_UINT8 , BASE_DEC , VALS ( zbee_zcl_color_control_direction_values ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_transit_time , {
 "Transition Time" , "zbee_zcl_lighting.color_control.transit_time" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_100ms ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_move_mode , {
 "Move Mode" , "zbee_zcl_lighting.color_control.move_mode" , FT_UINT8 , BASE_DEC , VALS ( zbee_zcl_color_control_move_mode ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_rate , {
 "Rate" , "zbee_zcl_lighting.color_control.rate" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_step_mode , {
 "Step Mode" , "zbee_zcl_lighting.color_control.step_mode" , FT_UINT8 , BASE_DEC , VALS ( zbee_zcl_color_control_step_mode ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_step_size , {
 "Step Size" , "zbee_zcl_lighting.color_control.step_size" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_transit_time_8bit , {
 "Transition Time" , "zbee_zcl_lighting.color_control.transition_time_8bit" , FT_UINT8 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_100ms ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_saturation , {
 "Saturation" , "zbee_zcl_lighting.color_control.saturation" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_X , {
 "Color X" , "zbee_zcl_lighting.color_control.color_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_Y , {
 "Color Y" , "zbee_zcl_lighting.color_control.color_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_rate_X , {
 "Rate X" , "zbee_zcl_lighting.color_control.rate_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_rate_Y , {
 "Rate Y" , "zbee_zcl_lighting.color_control.rate_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_step_X , {
 "Step X" , "zbee_zcl_lighting.color_control.step_x" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_step_Y , {
 "Step Y" , "zbee_zcl_lighting.color_control.step_y" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_xy ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_temp , {
 "Color temperature" , "zbee_zcl_lighting.color_control.color_temp" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_temperature ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_enhanced_hue , {
 "Enhanced Hue" , "zbee_zcl_lighting.color_control.enhanced_hue" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_enhanced_rate , {
 "Enhanced Rate" , "zbee_zcl_lighting.color_control.enhanced_rate" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_enhanced_step_size , {
 "Enhanced Step Size" , "zbee_zcl_lighting.color_control.enhanced_step_size" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_loop_update_flags , {
 "Update Flags" , "zbee_zcl_lighting.color_control.color_loop_update" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_loop_update_action , {
 "Update Action" , "zbee_zcl_lighting.color_control.color_loop_update.action" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_COLOR_LOOP_UPDATE_ACTION_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_loop_update_direction , {
 "Update Direction" , "zbee_zcl_lighting.color_control.color_loop_update.direction" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_COLOR_LOOP_UPDATE_DIRECTION_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_loop_update_time , {
 "Update Time" , "zbee_zcl_lighting.color_control.color_loop_update.time" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_COLOR_LOOP_UPDATE_TIME_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_loop_update_start_hue , {
 "Update Start Hue" , "zbee_zcl_lighting.color_control.color_loop_update.start_hue" , FT_UINT8 , BASE_DEC , NULL , ZBEE_ZCL_COLOR_LOOP_UPDATE_START_HUE_MASK , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_loop_action , {
 "Action" , "zbee_zcl_lighting.color_control.color_loop_action" , FT_UINT8 , BASE_DEC , VALS ( zbee_zcl_color_control_action ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_loop_direction , {
 "Direction" , "zbee_zcl_lighting.color_control.color_loop_direction" , FT_UINT8 , BASE_DEC , VALS ( zbee_zcl_color_control_color_loop_direction_values ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_loop_time , {
 "Time" , "zbee_zcl_lighting.color_control.color_loop_time" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_zcl_time_in_seconds ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_loop_start_hue , {
 "Enhanced Hue" , "zbee_zcl_lighting.color_control.color_loop_start_hue" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_temp_min , {
 "Color Temperature Minimum Mired" , "zbee_zcl_lighting.color_control.color_temp_min" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_temperature ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_color_temp_max , {
 "Color Temperature Maximum Mired" , "zbee_zcl_lighting.color_control.color_temp_max" , FT_UINT16 , BASE_CUSTOM , CF_FUNC ( decode_color_temperature ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_color_control_srv_rx_cmd_id , {
 "Command" , "zbee_zcl_lighting.color_control.cmd.srv_rx.id" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_color_control_srv_rx_cmd_names ) , 0x00 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ZBEE_ZCL_COLOR_CONTROL_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_color_control ;
 ett [ 1 ] = & ett_zbee_zcl_color_control_color_capabilities ;
 ett [ 2 ] = & ett_zbee_zcl_color_control_color_loop_settings ;
 proto_zbee_zcl_color_control = proto_register_protocol ( "ZigBee ZCL Color Control" , "ZCL Color Control" , ZBEE_PROTOABBREV_ZCL_COLOR_CONTROL ) ;
 proto_register_field_array ( proto_zbee_zcl_color_control , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_COLOR_CONTROL , dissect_zbee_zcl_color_control , proto_zbee_zcl_color_control ) ;
 }