void proto_register_zbee_zcl_met_idt ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_met_idt_attr_id , {
 "Attribute" , "zbee_zcl_ha.metidt.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_met_idt_attr_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_met_idt_meter_type_id , {
 "Meter Type ID" , "zbee_zcl_ha.metidt.attr.meter_type.id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_met_idt_meter_type_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_met_idt_data_quality_id , {
 "Data Quality ID" , "zbee_zcl_ha.metidt.attr.data_quality.id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_met_idt_data_quality_names ) , 0x00 , NULL , HFILL }
 }
 }
 ;
 proto_zbee_zcl_met_idt = proto_register_protocol ( "ZigBee ZCL Meter Identification" , "ZCL Meter Identification" , ZBEE_PROTOABBREV_ZCL_METIDT ) ;
 proto_register_field_array ( proto_zbee_zcl_met_idt , hf , array_length ( hf ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_METIDT , dissect_zbee_zcl_met_idt , proto_zbee_zcl_met_idt ) ;
 }