void dissect_zcl_ballast_configuration_attr_data ( proto_tree * tree , tvbuff_t * tvb , guint * offset , guint16 attr_id , guint data_type ) {
 static const int * ballast_status [ ] = {
 & hf_zbee_zcl_ballast_configuration_status_non_operational , & hf_zbee_zcl_ballast_configuration_status_lamp_not_in_socket , NULL }
 ;
 static const int * lamp_alarm_mode [ ] = {
 & hf_zbee_zcl_ballast_configuration_lamp_alarm_mode_lamp_burn_hours , NULL }
 ;
 switch ( attr_id ) {
 case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_BALLAST_STATUS : proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_ballast_configuration_status , ett_zbee_zcl_ballast_configuration_status , ballast_status , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_LAMP_ALARM_MODE : proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_ballast_configuration_lamp_alarm_mode , ett_zbee_zcl_ballast_configuration_lamp_alarm_mode , lamp_alarm_mode , ENC_LITTLE_ENDIAN ) ;
 * offset += 1 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_PHYSICAL_MIN_LEVEL : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_PHYSICAL_MAX_LEVEL : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_MIN_LEVEL : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_MAX_LEVEL : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_POWER_ON_LEVEL : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_POWER_ON_FADE_TIME : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_INTRINSIC_BALLAST_FACTOR : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_BALLAST_FACT_ADJ : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_LAMP_QUANTITY : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_LAMP_TYPE : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_LAMP_MANUFACTURER : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_LAMP_RATED_HOURS : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_LAMP_BURN_HOURS : case ZBEE_ZCL_ATTR_ID_BALLAST_CONFIGURATION_LAMP_BURN_HOURS_TRIP_POINT : default : dissect_zcl_attr_data ( tvb , tree , offset , data_type ) ;
 break ;
 }
 }