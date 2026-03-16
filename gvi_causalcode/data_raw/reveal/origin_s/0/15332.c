void proto_reg_handoff_nlm ( void ) {
 rpc_init_prog ( proto_nlm , NLM_PROGRAM , ett_nlm , G_N_ELEMENTS ( nlm_vers_info ) , nlm_vers_info ) ;
 }