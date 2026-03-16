void proto_register_steam_ihs_discovery ( void ) {
 module_t * steam_ihs_discovery_module ;
 expert_module_t * expert_steam_ihs_discovery ;
 static hf_register_info hf [ ] = {
 {
 & hf_steam_ihs_discovery_signature , {
 "Signature" , "steam_ihs_discovery.signature" , FT_UINT64 , BASE_HEX , NULL , 0 , "Every packet of the Steam In-Home Streaming Discovery Protocol begins with this signature." , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_header_length , {
 "Header Length" , "steam_ihs_discovery.header_length" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_length , {
 "Body Length" , "steam_ihs_discovery.body_length" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_unknown_data , {
 "Unknown Data" , "steam_ihs_discovery.unknown_data" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_unknown_number , {
 "Unknown Number" , "steam_ihs_discovery.unknown_number" , FT_UINT64 , BASE_DEC_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_header_clientid , {
 "Client ID" , "steam_ihs_discovery.header_client_id" , FT_UINT64 , BASE_DEC_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_header_msgtype , {
 "Message Type" , "steam_ihs_discovery.header_msg_type" , FT_UINT64 , BASE_DEC | BASE_VAL64_STRING , VALS64 ( hf_steam_ihs_discovery_header_msgtype_strings ) , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_header_instanceid , {
 "Instance ID" , "steam_ihs_discovery.header_instance_id" , FT_UINT64 , BASE_DEC_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_discovery_seqnum , {
 "Sequence Number" , "steam_ihs_discovery.body_discovery_seqnum" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_discovery_clientids , {
 "Client IDs" , "steam_ihs_discovery.body_discovery_clientids" , FT_UINT64 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_version , {
 "Version" , "steam_ihs_discovery.body_status_version" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_minversion , {
 "Minimum Version" , "steam_ihs_discovery.body_status_minversion" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_connectport , {
 "Connect Port" , "steam_ihs_discovery.body_status_connectport" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_hostname , {
 "Hostname" , "steam_ihs_discovery.body_status_hostname" , FT_STRING , STR_UNICODE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_enabledservices , {
 "Enabled Services" , "steam_ihs_discovery.body_status_enabledservices" , FT_UINT32 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_ostype , {
 "OS Type" , "steam_ihs_discovery.body_status_ostype" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_is64bit , {
 "Is 64 Bit" , "steam_ihs_discovery.body_status_is64bit" , FT_BOOLEAN , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_euniverse , {
 "EUniverse" , "steam_ihs_discovery.body_status_euniverse" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_timestamp , {
 "Timestamp" , "steam_ihs_discovery.body_status_timestamp" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_screenlocked , {
 "Screen Locked" , "steam_ihs_discovery.body_status_screenlocked" , FT_BOOLEAN , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_gamesrunning , {
 "Games Running" , "steam_ihs_discovery.body_status_gamesrunning" , FT_BOOLEAN , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_macaddresses , {
 "MAC Addresses" , "steam_ihs_discovery.body_status_macaddresses" , FT_STRING , STR_ASCII , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_user_steamid , {
 "Steam ID" , "steam_ihs_discovery.body_status_user_steamid" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_status_user_authkeyid , {
 "Auth Key ID" , "steam_ihs_discovery.body_status_user_authkeyid" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_authrequest_devicetoken , {
 "Device Token" , "steam_ihs_discovery.body_authrequest_devicetoken" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_authrequest_devicename , {
 "Device Name" , "steam_ihs_discovery.body_authrequest_devicename" , FT_STRING , STR_UNICODE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_authrequest_encryptedrequest , {
 "Encrypted Request" , "steam_ihs_discovery.body_authrequest_encryptedrequest" , FT_BYTES , BASE_NO_DISPLAY_VALUE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_authresponse_authresult , {
 "Result" , "steam_ihs_discovery.body_authresponse_authresult" , FT_UINT64 , BASE_DEC | BASE_VAL64_STRING , VALS64 ( hf_steam_ihs_discovery_body_authresponse_authresult_strings ) , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_requestid , {
 "Request ID" , "steam_ihs_discovery.body_streamingrequest_requestid" , FT_UINT32 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_maximumresolutionx , {
 "Maximum Resolution X" , "steam_ihs_discovery.body_streamingrequest_maximumresolutionx" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_maximumresolutiony , {
 "Maximum Resolution Y" , "steam_ihs_discovery.body_streamingrequest_maximumresolutiony" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_audiochannelcount , {
 "Audio Channel Count" , "steam_ihs_discovery.body_streamingrequest_audiochannelcount" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_deviceversion , {
 "Device Version" , "steam_ihs_discovery.body_streamingrequest_deviceversion" , FT_STRING , STR_UNICODE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_streamdesktop , {
 "Stream Desktop" , "steam_ihs_discovery.body_streamingrequest_streamdesktop" , FT_BOOLEAN , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_devicetoken , {
 "Device Token" , "steam_ihs_discovery.body_streamingrequest_devicetoken" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_pin , {
 "PIN" , "steam_ihs_discovery.body_streamingrequest_pin" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_enablevideostreaming , {
 "Enable Video Streaming" , "steam_ihs_discovery.body_streamingrequest_enablevideostreaming" , FT_BOOLEAN , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_enableaudiostreaming , {
 "Enable Audio Streaming" , "steam_ihs_discovery.body_streamingrequest_enableaudiostreaming" , FT_BOOLEAN , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingrequest_enableinputstreaming , {
 "Enable Input Streaming" , "steam_ihs_discovery.body_streamingrequest_enableinputstreaming" , FT_BOOLEAN , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingcancelrequest_requestid , {
 "Request ID" , "steam_ihs_discovery.body_streamingcancelrequest_requestid" , FT_UINT32 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingresponse_requestid , {
 "Request ID" , "steam_ihs_discovery.body_streamingresponse_requestid" , FT_UINT32 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingresponse_result , {
 "Result" , "steam_ihs_discovery.body_streamingresponse_result" , FT_UINT64 , BASE_DEC | BASE_VAL64_STRING , VALS64 ( hf_steam_ihs_discovery_body_streamingresponse_result_strings ) , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingresponse_port , {
 "Port" , "steam_ihs_discovery.body_streamingresponse_port" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingresponse_encryptedsessionkey , {
 "Encrypted Session Key" , "steam_ihs_discovery.body_streamingresponse_encryptedsessionkey" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_streamingresponse_virtualherelicenseddevicecount , {
 "VirtualHere Licensed Device Count" , "steam_ihs_discovery.body_streamingresponse_virtualherelicenseddevicecount" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_proofrequest_challenge , {
 "Challenge" , "steam_ihs_discovery.body_proofrequest_challenge" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_steam_ihs_discovery_body_proofresponse_response , {
 "Response" , "steam_ihs_discovery.body_proofresponse_response" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ] = {
 & ett_steam_ihs_discovery , & ett_steam_ihs_discovery_body_status_user }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_steam_ihs_discovery_unknown_data , {
 "steam_ihs_discovery.unknowndata" , PI_UNDECODED , PI_WARN , "Unknown data section" , EXPFILL }
 }
 , {
 & ei_steam_ihs_discovery_unknown_number , {
 "steam_ihs_discovery.unknownnumber" , PI_UNDECODED , PI_WARN , "Unknown numeric protobuf field" , EXPFILL }
 }
 , {
 & ei_steam_ihs_discovery_unknown_lengthdelimited , {
 "steam_ihs_discovery.unknownlengthdelimited" , PI_UNDECODED , PI_WARN , "Unknown length-delimited protobuf field" , EXPFILL }
 }
 , {
 & ei_steam_ihs_discovery_invalid_wiretype , {
 "steam_ihs_discovery.invalid_wiretype" , PI_MALFORMED , PI_ERROR , "Unexpected wire type" , EXPFILL }
 }
 , {
 & ei_steam_ihs_discovery_invalid_length , {
 "steam_ihs_discovery.invalid_length" , PI_MALFORMED , PI_ERROR , "Length-delimited field has invalid length" , EXPFILL }
 }
 }
 ;
 proto_steam_ihs_discovery = proto_register_protocol ( "Steam In-Home Streaming Discovery Protocol" , "Steam IHS Discovery" , "steam_ihs_discovery" ) ;
 proto_register_field_array ( proto_steam_ihs_discovery , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_steam_ihs_discovery = expert_register_protocol ( proto_steam_ihs_discovery ) ;
 expert_register_field_array ( expert_steam_ihs_discovery , ei , array_length ( ei ) ) ;
 steam_ihs_discovery_module = prefs_register_protocol ( proto_steam_ihs_discovery , proto_reg_handoff_steam_ihs_discovery ) ;
 prefs_register_uint_preference ( steam_ihs_discovery_module , "udp.port" , "steam_ihs_discovery UDP Port" , " Steam IHS Discovery UDP port if other than the default" , 10 , & udp_port_pref ) ;
 }