void proto_reg_handoff_mswsp ( void ) {
 heur_dissector_add ( "smb_transact" , dissect_mswsp_smb , "WSP over SMB1" , "smb1_wsp" , proto_mswsp , HEURISTIC_ENABLE ) ;
 heur_dissector_add ( "smb2_pipe_subdissectors" , dissect_mswsp_smb2 , "WSP over SMB2" , "smb2_wsp" , proto_mswsp , HEURISTIC_ENABLE ) ;
 }