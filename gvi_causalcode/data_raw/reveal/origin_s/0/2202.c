void proto_register_pkt_ccc ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_pkt_ccc_id , {
 "PacketCable CCC Identifier" , "pkt_ccc.ccc_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pkt_ccc_ts , {
 "PacketCable CCC Timestamp" , "pkt_ccc.ts" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_UTC , NULL , 0x0 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_pkt_ccc , }
 ;
 module_t * pkt_ccc_module ;
 proto_pkt_ccc = proto_register_protocol ( "PacketCable Call Content Connection" , "PKT CCC" , "pkt_ccc" ) ;
 proto_register_field_array ( proto_pkt_ccc , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 new_register_dissector ( "pkt_ccc" , dissect_pkt_ccc , proto_pkt_ccc ) ;
 pkt_ccc_module = prefs_register_protocol ( proto_pkt_ccc , proto_reg_handoff_pkt_ccc ) ;
 prefs_register_uint_preference ( pkt_ccc_module , "udp_port" , "UDP port" , "Decode packets on this UDP port as PacketCable CCC" , 10 , & global_pkt_ccc_udp_port ) ;
 }