void proto_register_zbee_zcl_appl_idt ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_zbee_zcl_appl_idt_attr_id , {
 "Attribute" , "zbee_zcl_ha.applident.attr_id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_appl_idt_attr_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_idt_company_id , {
 "Company ID" , "zbee_zcl_ha.applident.attr.company.id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_appl_idt_company_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_idt_brand_id , {
 "Brand ID" , "zbee_zcl_ha.applident.attr.brand.id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_appl_idt_brand_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_idt_string_len , {
 "Length" , "zbee_zcl_ha.applident.string.len" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_idt_prod_type_name , {
 "Product Type Name" , "zbee_zcl_ha.applident.attr.prod_type.name" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_appl_idt_prod_type_name_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_idt_prod_type_id , {
 "Product Type ID" , "zbee_zcl_ha.applident.attr.prod_type.id" , FT_UINT16 , BASE_HEX , VALS ( zbee_zcl_appl_idt_prod_type_names ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_zbee_zcl_appl_idt_ceced_spec_ver , {
 "CECED Spec. Version" , "zbee_zcl_ha.applident.attr.ceced_spec_ver" , FT_UINT8 , BASE_HEX , VALS ( zbee_zcl_appl_idt_ceced_spec_ver_names ) , 0x00 , NULL , HFILL }
 }
 }
 ;
 gint * ett [ ZBEE_ZCL_APPL_IDT_NUM_ETT ] ;
 ett [ 0 ] = & ett_zbee_zcl_appl_idt ;
 ett [ 1 ] = & ett_zbee_zcl_appl_idt_basic ;
 proto_zbee_zcl_appl_idt = proto_register_protocol ( "ZigBee ZCL Appliance Identification" , "ZCL Appliance Identification" , ZBEE_PROTOABBREV_ZCL_APPLIDT ) ;
 proto_register_field_array ( proto_zbee_zcl_appl_idt , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 register_dissector ( ZBEE_PROTOABBREV_ZCL_APPLIDT , dissect_zbee_zcl_appl_idt , proto_zbee_zcl_appl_idt ) ;
 }