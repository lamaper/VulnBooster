void proto_reg_handoff_umts_mac ( void ) {
 rlc_pcch_handle = find_dissector_add_dependency ( "rlc.pcch" , proto_umts_mac ) ;
 rlc_ccch_handle = find_dissector_add_dependency ( "rlc.ccch" , proto_umts_mac ) ;
 rlc_ctch_handle = find_dissector_add_dependency ( "rlc.ctch" , proto_umts_mac ) ;
 rlc_dcch_handle = find_dissector_add_dependency ( "rlc.dcch" , proto_umts_mac ) ;
 rlc_ps_dtch_handle = find_dissector_add_dependency ( "rlc.ps_dtch" , proto_umts_mac ) ;
 rrc_handle = find_dissector_add_dependency ( "rrc" , proto_umts_mac ) ;
 }