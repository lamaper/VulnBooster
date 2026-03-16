void dissect_zcl_met_idt_attr_data ( proto_tree * tree , tvbuff_t * tvb , guint * offset , guint16 attr_id , guint data_type ) {
 switch ( attr_id ) {
 case ZBEE_ZCL_ATTR_ID_MET_IDT_METER_TYPE_ID : proto_tree_add_item ( tree , hf_zbee_zcl_met_idt_meter_type_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 case ZBEE_ZCL_ATTR_ID_MET_IDT_DATA_QUALITY_ID : proto_tree_add_item ( tree , hf_zbee_zcl_met_idt_data_quality_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 break ;
 default : dissect_zcl_attr_data ( tvb , tree , offset , data_type ) ;
 break ;
 }
 }