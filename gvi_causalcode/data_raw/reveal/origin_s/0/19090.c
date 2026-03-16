void proto_reg_handoff_gsm_a_dtap ( void ) {
 dissector_handle_t dtap_handle ;
 dtap_handle = find_dissector ( "gsm_a_dtap" ) ;
 dissector_add_uint ( "bssap.pdu_type" , BSSAP_PDU_TYPE_DTAP , dtap_handle ) ;
 dissector_add_uint ( "ranap.nas_pdu" , BSSAP_PDU_TYPE_DTAP , dtap_handle ) ;
 dissector_add_uint ( "llcgprs.sapi" , 1 , dtap_handle ) ;
 dissector_add_uint ( "llcgprs.sapi" , 7 , dtap_handle ) ;
 dissector_add_uint ( "lapdm.sapi" , 0 , dtap_handle ) ;
 dissector_add_uint ( "lapdm.sapi" , 3 , dtap_handle ) ;
 gsm_map_handle = find_dissector_add_dependency ( "gsm_map" , proto_a_dtap ) ;
 rp_handle = find_dissector_add_dependency ( "gsm_a_rp" , proto_a_dtap ) ;
 }