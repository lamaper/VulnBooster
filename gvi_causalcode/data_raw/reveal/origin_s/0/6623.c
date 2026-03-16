void proto_register_bta2dp ( void ) {
 module_t * module ;
 static hf_register_info hf [ ] = {
 {
 & hf_bta2dp_acp_seid , {
 "ACP SEID" , "bta2dp.acp_seid" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_bta2dp_int_seid , {
 "INT SEID" , "bta2dp.int_seid" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_bta2dp_codec , {
 "Codec" , "bta2dp.codec" , FT_UINT8 , BASE_HEX , VALS ( media_codec_audio_type_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_bta2dp_vendor_id , {
 "Vendor ID" , "bta2dp.codec.vendor.vendor_id" , FT_UINT32 , BASE_HEX | BASE_EXT_STRING , & bluetooth_company_id_vals_ext , 0x00 , NULL , HFILL }
 }
 , {
 & hf_bta2dp_vendor_codec_id , {
 "Vendor Codec" , "bta2dp.codec.vendor.codec_id" , FT_UINT16 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_bta2dp_content_protection , {
 "Content Protection" , "bta2dp.content_protection" , FT_UINT16 , BASE_HEX , VALS ( content_protection_type_vals ) , 0x0000 , NULL , HFILL }
 }
 , {
 & hf_bta2dp_stream_start_in_frame , {
 "Stream Start in Frame" , "bta2dp.stream_start_in_frame" , FT_FRAMENUM , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_bta2dp_stream_end_in_frame , {
 "Stream End in Frame" , "bta2dp.stream_end_in_frame" , FT_FRAMENUM , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_bta2dp_stream_number , {
 "Stream Number" , "bta2dp.stream_number" , FT_UINT32 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ] = {
 & ett_bta2dp }
 ;
 proto_bta2dp = proto_register_protocol ( "Bluetooth A2DP Profile" , "BT A2DP" , "bta2dp" ) ;
 proto_register_field_array ( proto_bta2dp , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 bta2dp_handle = register_dissector ( "bta2dp" , dissect_bta2dp , proto_bta2dp ) ;
 module = prefs_register_protocol_subtree ( "Bluetooth" , proto_bta2dp , NULL ) ;
 prefs_register_static_text_preference ( module , "a2dp.version" , "Bluetooth Profile A2DP version: 1.3" , "Version of profile supported by this dissector." ) ;
 prefs_register_bool_preference ( module , "a2dp.content_protection.scms_t" , "Force SCMS-T decoding" , "Force decoding stream as A2DP with Content Protection SCMS-T " , & force_a2dp_scms_t ) ;
 prefs_register_enum_preference ( module , "a2dp.codec" , "Force codec" , "Force decoding stream as A2DP with specified codec" , & force_a2dp_codec , pref_a2dp_codec , FALSE ) ;
 }