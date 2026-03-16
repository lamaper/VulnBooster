void dissect_zcl_power_config_attr_data ( proto_tree * tree , tvbuff_t * tvb , guint * offset , guint16 attr_id , guint data_type ) {
 proto_item * it ;
 static const int * mains_alarm_mask [ ] = {
 & hf_zbee_zcl_power_config_mains_alarm_mask_low , & hf_zbee_zcl_power_config_mains_alarm_mask_high , & hf_zbee_zcl_power_config_mains_alarm_mask_reserved , NULL }
 ;
 static const int * batt_alarm_mask [ ] = {
 & hf_zbee_zcl_power_config_batt_alarm_mask_low , & hf_zbee_zcl_power_config_batt_alarm_mask_reserved , NULL }
 ;
 switch ( attr_id ) {
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_MAINS_VOLTAGE : proto_tree_add_item ( tree , hf_zbee_zcl_power_config_mains_voltage , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_MAINS_FREQUENCY : proto_tree_add_item ( tree , hf_zbee_zcl_power_config_mains_frequency , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_MAINS_ALARM_MASK : proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_power_config_mains_alarm_mask , ett_zbee_zcl_power_config_mains_alarm_mask , mains_alarm_mask , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_MAINS_VOLTAGE_MIN_THR : proto_tree_add_item ( tree , hf_zbee_zcl_power_config_mains_voltage_min_thr , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_MAINS_VOLTAGE_MAX_THR : proto_tree_add_item ( tree , hf_zbee_zcl_power_config_mains_voltage_max_thr , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_MAINS_VOLTAGE_DWELL_TP : it = proto_tree_add_item ( tree , hf_zbee_zcl_power_config_mains_voltage_dwell_tp , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_item_append_text ( it , " [s]" ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_BATTERY_SIZE : proto_tree_add_item ( tree , hf_zbee_zcl_power_config_batt_type , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_BATTERY_VOLTAGE : proto_tree_add_item ( tree , hf_zbee_zcl_power_config_batt_voltage , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_BATTERY_AH_RATING : proto_tree_add_item ( tree , hf_zbee_zcl_power_config_batt_ah_rating , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_BATTERY_RATED_VOLTAGE : proto_tree_add_item ( tree , hf_zbee_zcl_power_config_batt_rated_voltage , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_BATTERY_ALARM_MASK : proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_power_config_batt_alarm_mask , ett_zbee_zcl_power_config_batt_alarm_mask , batt_alarm_mask , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_BATTERY_VOLTAGE_MIN_THR : proto_tree_add_item ( tree , hf_zbee_zcl_power_config_batt_voltage_min_thr , tvb , * offset , 1 , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_POWER_CONF_BATTERY_MANUFACTURER : case ZBEE_ZCL_ATTR_ID_POWER_CONF_BATTERY_QUANTITY : default : dissect_zcl_attr_data ( tvb , tree , offset , data_type ) ;
 break ;
 }
 }