void proto_register_applemidi ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_applemidi_signature , {
 "Signature" , "applemidi.signature" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_command , {
 "Command" , "applemidi.command" , FT_UINT16 , BASE_HEX , VALS ( applemidi_commands ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_protocol_version , {
 "Protocol Version" , "applemidi.protocol_version" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_token , {
 "Initiator Token" , "applemidi.initiator_token" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_ssrc , {
 "Sender SSRC" , "applemidi.sender_ssrc" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_name , {
 "Name" , "applemidi.name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_count , {
 "Count" , "applemidi.count" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_padding , {
 "Padding" , "applemidi.padding" , FT_UINT24 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_timestamp1 , {
 "Timestamp 1" , "applemidi.timestamp1" , FT_UINT64 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_timestamp2 , {
 "Timestamp 2" , "applemidi.timestamp2" , FT_UINT64 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_timestamp3 , {
 "Timestamp 3" , "applemidi.timestamp3" , FT_UINT64 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_sequence_num , {
 "Sequence Number" , "applemidi.sequence_number" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_rtp_sequence_num , {
 "RTP Sequence Number" , "applemidi.rtp_sequence_number" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_rtp_bitrate_limit , {
 "Bitrate limit" , "applemidi.bitrate_limit" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_applemidi_unknown_data , {
 "Unknown Data" , "applemidi.unknown_data" , FT_BYTES , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_applemidi , & ett_applemidi_seq_num }
 ;
 proto_applemidi = proto_register_protocol ( APPLEMIDI_DISSECTOR_NAME , APPLEMIDI_DISSECTOR_SHORTNAME , APPLEMIDI_DISSECTOR_ABBREVIATION ) ;
 proto_register_field_array ( proto_applemidi , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 }