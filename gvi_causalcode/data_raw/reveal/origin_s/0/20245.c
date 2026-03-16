void proto_reg_handoff_zbee_zcl_ballast_configuration ( void ) {
 zbee_zcl_init_cluster ( ZBEE_PROTOABBREV_ZCL_BALLAST_CONFIG , proto_zbee_zcl_ballast_configuration , ett_zbee_zcl_ballast_configuration , ZBEE_ZCL_CID_BALLAST_CONFIG , ZBEE_MFG_CODE_NONE , hf_zbee_zcl_ballast_configuration_attr_id , - 1 , - 1 , ( zbee_zcl_fn_attr_data ) dissect_zcl_ballast_configuration_attr_data ) ;
 }