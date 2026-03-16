void proto_reg_handoff_cipsafety ( void ) {
 dissector_handle_t cip_class_s_supervisor_handle ;
 cip_class_s_supervisor_handle = create_dissector_handle ( dissect_cip_class_s_supervisor , proto_cip_class_s_supervisor ) ;
 dissector_add_uint ( "cip.class.iface" , CI_CLS_SAFETY_SUPERVISOR , cip_class_s_supervisor_handle ) ;
 cip_class_s_validator_handle = create_dissector_handle ( dissect_cip_class_s_validator , proto_cip_class_s_validator ) ;
 dissector_add_uint ( "cip.class.iface" , CI_CLS_SAFETY_VALIDATOR , cip_class_s_validator_handle ) ;
 heur_dissector_add ( "cip.sc" , dissect_class_svalidator_heur , "CIP Safety Validator" , "s_validator_cip" , proto_cip_class_s_validator , HEURISTIC_ENABLE ) ;
 dissector_add_for_decode_as ( "enip.io" , cipsafety_handle ) ;
 proto_cip = proto_get_id_by_filter_name ( "cip" ) ;
 subdissector_class_table = find_dissector_table ( "cip.class.iface" ) ;
 }