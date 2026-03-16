void proto_reg_handoff_zbee_zcl_met_idt ( void ) {
 zbee_zcl_init_cluster ( proto_zbee_zcl_met_idt , ett_zbee_zcl_met_idt , ZBEE_ZCL_CID_METER_IDENTIFICATION , hf_zbee_zcl_met_idt_attr_id , - 1 , - 1 , ( zbee_zcl_fn_attr_data ) dissect_zcl_met_idt_attr_data ) ;
 }