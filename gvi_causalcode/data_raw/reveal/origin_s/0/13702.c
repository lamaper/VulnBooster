void proto_reg_handoff_rsl ( void ) {
 dissector_handle_t rsl_handle ;
 rsl_handle = create_dissector_handle ( dissect_rsl , proto_rsl ) ;
 dissector_add_uint ( "lapd.gsm.sapi" , LAPD_GSM_SAPI_RA_SIG_PROC , rsl_handle ) ;
 gsm_cbch_handle = find_dissector ( "gsm_cbch" ) ;
 gsm_cbs_handle = find_dissector ( "gsm_cbs" ) ;
 gsm_a_ccch_handle = find_dissector ( "gsm_a_ccch" ) ;
 gsm_a_dtap_handle = find_dissector ( "gsm_a_dtap" ) ;
 gsm_a_sacch_handle = find_dissector ( "gsm_a_sacch" ) ;
 }