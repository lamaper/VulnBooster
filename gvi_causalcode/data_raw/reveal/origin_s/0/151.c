void dissect_zcl_basic_attr_data ( proto_tree * tree , tvbuff_t * tvb , guint * offset , guint16 attr_id , guint data_type ) {
 static const int * alarm_mask [ ] = {
 & hf_zbee_zcl_basic_alarm_mask_gen_hw_fault , & hf_zbee_zcl_basic_alarm_mask_gen_sw_fault , & hf_zbee_zcl_basic_alarm_mask_reserved , NULL }
 ;
 static const int * local_cfg [ ] = {
 & hf_zbee_zcl_basic_disable_local_cfg_reset , & hf_zbee_zcl_basic_disable_local_cfg_device_cfg , & hf_zbee_zcl_basic_disable_local_cfg_reserved , NULL }
 ;
 switch ( attr_id ) {
 case ZBEE_ZCL_ATTR_ID_BASIC_POWER_SOURCE : proto_tree_add_item ( tree , hf_zbee_zcl_basic_pwr_src , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_BASIC_DEVICE_ENABLED : proto_tree_add_item ( tree , hf_zbee_zcl_basic_dev_en , tvb , * offset , 1 , ENC_NA ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_BASIC_ALARM_MASK : proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_basic_alarm_mask , ett_zbee_zcl_basic_alarm_mask , alarm_mask , ENC_NA ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_BASIC_DISABLE_LOCAL_CFG : proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_basic_disable_local_cfg , ett_zbee_zcl_basic_dis_local_cfg , local_cfg , ENC_NA ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_BASIC_ZCL_VERSION : case ZBEE_ZCL_ATTR_ID_BASIC_APPL_VERSION : case ZBEE_ZCL_ATTR_ID_BASIC_STACK_VERSION : case ZBEE_ZCL_ATTR_ID_BASIC_HW_VERSION : case ZBEE_ZCL_ATTR_ID_BASIC_MANUFACTURER_NAME : case ZBEE_ZCL_ATTR_ID_BASIC_MODEL_ID : case ZBEE_ZCL_ATTR_ID_BASIC_DATE_CODE : case ZBEE_ZCL_ATTR_ID_BASIC_PHY_ENVIRONMENT : case ZBEE_ZCL_ATTR_ID_BASIC_LOCATION_DESCR : default : dissect_zcl_attr_data ( tvb , tree , offset , data_type ) ;
 break ;
 }
 }