static void dissect_zcl_appl_ctrl_attr_data ( proto_tree * tree , tvbuff_t * tvb , guint * offset , guint16 attr_id , guint data_type ) {
 static const int * flags [ ] = {
 & hf_zbee_zcl_appl_ctrl_time_mm , & hf_zbee_zcl_appl_ctrl_time_encoding_type , & hf_zbee_zcl_appl_ctrl_time_hh , NULL }
 ;
 switch ( attr_id ) {
 case ZBEE_ZCL_ATTR_ID_APPL_CTRL_START_TIME : case ZBEE_ZCL_ATTR_ID_APPL_CTRL_FINISH_TIME : case ZBEE_ZCL_ATTR_ID_APPL_CTRL_REMAINING_TIME : proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_appl_ctrl_time , ett_zbee_zcl_appl_ctrl_time , flags , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 default : dissect_zcl_attr_data ( tvb , tree , offset , data_type ) ;
 break ;
 }
 }