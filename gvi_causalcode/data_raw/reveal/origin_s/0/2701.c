void proto_register_netbios ( void ) {
 static gint * ett [ ] = {
 & ett_netb , & ett_netb_name , & ett_netb_flags , & ett_netb_status , & ett_netb_fragments , & ett_netb_fragment , }
 ;
 static hf_register_info hf_netb [ ] = {
 {
 & hf_netb_cmd , {
 "Command" , "netbios.command" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & cmd_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_hdr_len , {
 "Length" , "netbios.hdr_len" , FT_UINT16 , BASE_DEC , NULL , 0x0 , "Header Length" , HFILL }
 }
 , {
 & hf_netb_delimiter , {
 "Delimiter" , "netbios.delimiter" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_xmit_corrl , {
 "Transmit Correlator" , "netbios.xmit_corrl" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_resp_corrl , {
 "Response Correlator" , "netbios.resp_corrl" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_call_name_type , {
 "Caller's Name Type" , "netbios.call_name_type" , FT_UINT8 , BASE_HEX , VALS ( name_types ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_nb_name_type , {
 "NetBIOS Name Type" , "netbios.nb_name_type" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & nb_name_type_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_nb_name , {
 "NetBIOS Name" , "netbios.nb_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_version , {
 "NetBIOS Version" , "netbios.version" , FT_BOOLEAN , 8 , TFS ( & netb_version_str ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_netbios_no_receive_flags , {
 "Flags" , "netbios.no_receive_flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netbios_no_receive_flags_send_no_ack , {
 "SEND.NO.ACK data received" , "netbios.no_receive_flags.send_no_ack" , FT_BOOLEAN , 8 , TFS ( & tfs_no_yes ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_netb_largest_frame , {
 "Largest Frame" , "netbios.largest_frame" , FT_UINT8 , BASE_DEC , VALS ( max_frame_size_vals ) , 0x0E , NULL , HFILL }
 }
 , {
 & hf_netb_status_buffer_len , {
 "Length of status buffer" , "netbios.status_buffer_len" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_status , {
 "Status" , "netbios.status" , FT_UINT8 , BASE_DEC , VALS ( status_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_name_type , {
 "Name type" , "netbios.name_type" , FT_UINT16 , BASE_DEC , VALS ( name_types ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_max_data_recv_size , {
 "Maximum data receive size" , "netbios.max_data_recv_size" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_termination_indicator , {
 "Termination indicator" , "netbios.termination_indicator" , FT_UINT16 , BASE_HEX , VALS ( termination_indicator_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_num_data_bytes_accepted , {
 "Number of data bytes accepted" , "netbios.num_data_bytes_accepted" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_local_ses_no , {
 "Local Session No." , "netbios.local_session" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_remote_ses_no , {
 "Remote Session No." , "netbios.remote_session" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_flags , {
 "Flags" , "netbios.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_flags_send_no_ack , {
 "Handle SEND.NO.ACK" , "netbios.flags.send_no_ack" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_netb_flags_ack , {
 "Acknowledge" , "netbios.flags.ack" , FT_BOOLEAN , 8 , TFS ( & tfs_set_notset ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_netb_flags_ack_with_data , {
 "Acknowledge with data" , "netbios.flags.ack_with_data" , FT_BOOLEAN , 8 , TFS ( & flags_allowed ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_netb_flags_ack_expected , {
 "Acknowledge expected" , "netbios.flags.ack_expected" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_netb_flags_recv_cont_req , {
 "RECEIVE_CONTINUE requested" , "netbios.flags.recv_cont_req" , FT_BOOLEAN , 8 , TFS ( & tfs_yes_no ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_netb_data2 , {
 "DATA2 value" , "netbios.data2" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_data2_frame , {
 "Data length exceeds maximum frame size" , "netbios.data2.frame" , FT_BOOLEAN , 16 , TFS ( & tfs_yes_no ) , 0x8000 , NULL , HFILL }
 }
 , {
 & hf_netb_data2_user , {
 "Data length exceeds user's buffer" , "netbios.data2.user" , FT_BOOLEAN , 16 , TFS ( & tfs_yes_no ) , 0x4000 , NULL , HFILL }
 }
 , {
 & hf_netb_data2_status , {
 "Status data length" , "netbios.data2.status" , FT_UINT16 , BASE_DEC , NULL , 0x3FFF , NULL , HFILL }
 }
 , {
 & hf_netb_datagram_mac , {
 "Sender's MAC Address" , "netbios.datagram_mac" , FT_ETHER , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_datagram_bcast_mac , {
 "Sender's Node Address" , "netbios.datagram_bcast_mac" , FT_ETHER , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_resync_indicator , {
 "Re-sync indicator" , "netbios.resync_indicator" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_status_request , {
 "Status request" , "netbios.status_request" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_local_session_no , {
 "Local Session No." , "netbios.local_session_no" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_state_of_name , {
 "State of name" , "netbios.state_of_name" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_status_response , {
 "Status response" , "netbios.status_response" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_fragment_overlap , {
 "Fragment overlap" , "netbios.fragment.overlap" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , "Fragment overlaps with other fragments" , HFILL }
 }
 , {
 & hf_netb_fragment_overlap_conflict , {
 "Conflicting data in fragment overlap" , "netbios.fragment.overlap.conflict" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , "Overlapping fragments contained conflicting data" , HFILL }
 }
 , {
 & hf_netb_fragment_multiple_tails , {
 "Multiple tail fragments found" , "netbios.fragment.multipletails" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , "Several tails were found when defragmenting the packet" , HFILL }
 }
 , {
 & hf_netb_fragment_too_long_fragment , {
 "Fragment too long" , "netbios.fragment.toolongfragment" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , "Fragment contained data past end of packet" , HFILL }
 }
 , {
 & hf_netb_fragment_error , {
 "Defragmentation error" , "netbios.fragment.error" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , "Defragmentation error due to illegal fragments" , HFILL }
 }
 , {
 & hf_netb_fragment_count , {
 "Fragment count" , "netbios.fragment.count" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_fragment , {
 "NetBIOS Fragment" , "netbios.fragment" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_fragments , {
 "NetBIOS Fragments" , "netbios.fragments" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_netb_reassembled_length , {
 "Reassembled NetBIOS length" , "netbios.reassembled.length" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "The total length of the reassembled payload" , HFILL }
 }
 , }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_netb_unknown_command_data , {
 "netbios.unknown_command_data" , PI_UNDECODED , PI_WARN , "Unknown NetBIOS command data" , EXPFILL }
 }
 , }
 ;
 module_t * netbios_module ;
 expert_module_t * expert_netbios ;
 proto_netbios = proto_register_protocol ( "NetBIOS" , "NetBIOS" , "netbios" ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 proto_register_field_array ( proto_netbios , hf_netb , array_length ( hf_netb ) ) ;
 expert_netbios = expert_register_protocol ( proto_netbios ) ;
 expert_register_field_array ( expert_netbios , ei , array_length ( ei ) ) ;
 netbios_heur_subdissector_list = register_heur_dissector_list ( "netbios" , proto_netbios ) ;
 netbios_module = prefs_register_protocol ( proto_netbios , NULL ) ;
 prefs_register_bool_preference ( netbios_module , "defragment" , "Reassemble fragmented NetBIOS messages spanning multiple frames" , "Whether the NetBIOS dissector should defragment messages spanning multiple frames" , & netbios_defragment ) ;
 register_init_routine ( netbios_init ) ;
 register_cleanup_routine ( netbios_cleanup ) ;
 }