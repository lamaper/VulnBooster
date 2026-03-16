void proto_register_btvdp ( void ) {
 module_t * module ;
 expert_module_t * expert_btavdtp ;
 static hf_register_info hf [ ] = {
 {
 & hf_btvdp_acp_seid , {
 "ACP SEID" , "btvdp.acp_seid" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btvdp_int_seid , {
 "INT SEID" , "btvdp.int_seid" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btvdp_codec , {
 "Codec" , "btvdp.codec" , FT_UINT8 , BASE_HEX , VALS ( media_codec_video_type_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btvdp_vendor_id , {
 "Vendor ID" , "btvdp.codec.vendor.vendor_id" , FT_UINT32 , BASE_HEX | BASE_EXT_STRING , & bluetooth_company_id_vals_ext , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btvdp_vendor_codec_id , {
 "Vendor Codec" , "btvdp.codec.vendor.codec_id" , FT_UINT16 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btvdp_content_protection , {
 "Content Protection" , "btvdp.content_protection" , FT_UINT16 , BASE_HEX , VALS ( content_protection_type_vals ) , 0x0000 , NULL , HFILL }
 }
 , {
 & hf_btvdp_stream_start_in_frame , {
 "Stream Start in Frame" , "btvdp.stream_start_in_frame" , FT_FRAMENUM , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btvdp_stream_end_in_frame , {
 "Stream End in Frame" , "btvdp.stream_end_in_frame" , FT_FRAMENUM , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btvdp_stream_number , {
 "Stream Number" , "btvdp.stream_number" , FT_UINT32 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_btvdp }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_btavdtp_sbc_min_bitpool_out_of_range , {
 "btavdtp.codec.sbc.minimum_bitpool.out_of_range" , PI_PROTOCOL , PI_WARN , "Bitpool is out of range. Should be 2..250." , EXPFILL }
 }
 , {
 & ei_btavdtp_sbc_max_bitpool_out_of_range , {
 "btavdtp.codec.sbc.maximum_bitpool.out_of_range" , PI_PROTOCOL , PI_WARN , "Bitpool is out of range. Should be 2..250." , EXPFILL }
 }
 , {
 & ei_btavdtp_unexpected_losc_data , {
 "btavdtp.unexpected_losc_data" , PI_PROTOCOL , PI_WARN , "Unexpected losc data" , EXPFILL }
 }
 , }
 ;
 proto_btvdp = proto_register_protocol ( "Bluetooth VDP Profile" , "BT VDP" , "btvdp" ) ;
 btvdp_handle = register_dissector ( "btvdp" , dissect_btvdp , proto_btvdp ) ;
 proto_register_field_array ( proto_btvdp , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_btavdtp = expert_register_protocol ( proto_btvdp ) ;
 expert_register_field_array ( expert_btavdtp , ei , array_length ( ei ) ) ;
 module = prefs_register_protocol_subtree ( "Bluetooth" , proto_btvdp , NULL ) ;
 prefs_register_static_text_preference ( module , "vdp.version" , "Bluetooth Profile VDP version: 1.1" , "Version of profile supported by this dissector." ) ;
 prefs_register_bool_preference ( module , "vdp.content_protection.scms_t" , "Force SCMS-T decoding" , "Force decoding stream as VDP with Content Protection SCMS-T " , & force_vdp_scms_t ) ;
 prefs_register_enum_preference ( module , "vdp.codec" , "Force codec" , "Force decoding stream as VDP with specified codec" , & force_vdp_codec , pref_vdp_codec , FALSE ) ;
 }