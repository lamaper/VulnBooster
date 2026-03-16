void proto_reg_handoff_mpa ( void ) {
 heur_dissector_add ( "tcp" , dissect_iwarp_mpa , "IWARP_MPA over TCP" , "iwarp_mpa_tcp" , proto_iwarp_mpa , HEURISTIC_ENABLE ) ;
 ddp_rdmap_handle = find_dissector_add_dependency ( "iwarp_ddp_rdmap" , proto_iwarp_mpa ) ;
 }