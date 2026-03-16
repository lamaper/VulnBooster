static void dissect_netbios_payload ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree ) {
 heur_dtbl_entry_t * hdtbl_entry ;
 if ( ! dissector_try_heuristic ( netbios_heur_subdissector_list , tvb , pinfo , tree , & hdtbl_entry , NULL ) ) call_data_dissector ( tvb , pinfo , tree ) ;
 }