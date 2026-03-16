void proto_register_rtmpt ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_rtmpt_handshake_c0 , {
 "Protocol version" , "rtmpt.handshake.c0" , FT_BYTES , BASE_NONE , NULL , 0x0 , "RTMPT Handshake C0" , HFILL }
 }
 , {
 & hf_rtmpt_handshake_s0 , {
 "Protocol version" , "rtmpt.handshake.s0" , FT_BYTES , BASE_NONE , NULL , 0x0 , "RTMPT Handshake S0" , HFILL }
 }
 , {
 & hf_rtmpt_handshake_c1 , {
 "Handshake data" , "rtmpt.handshake.c1" , FT_BYTES , BASE_NONE , NULL , 0x0 , "RTMPT Handshake C1" , HFILL }
 }
 , {
 & hf_rtmpt_handshake_s1 , {
 "Handshake data" , "rtmpt.handshake.s1" , FT_BYTES , BASE_NONE , NULL , 0x0 , "RTMPT Handshake S1" , HFILL }
 }
 , {
 & hf_rtmpt_handshake_c2 , {
 "Handshake data" , "rtmpt.handshake.c2" , FT_BYTES , BASE_NONE , NULL , 0x0 , "RTMPT Handshake C2" , HFILL }
 }
 , {
 & hf_rtmpt_handshake_s2 , {
 "Handshake data" , "rtmpt.handshake.s2" , FT_BYTES , BASE_NONE , NULL , 0x0 , "RTMPT Handshake S2" , HFILL }
 }
 , {
 & hf_rtmpt_header_format , {
 "Format" , "rtmpt.header.format" , FT_UINT8 , BASE_DEC , NULL , 0xC0 , "RTMPT Basic Header format" , HFILL }
 }
 , {
 & hf_rtmpt_header_csid , {
 "Chunk Stream ID" , "rtmpt.header.csid" , FT_UINT8 , BASE_DEC , NULL , 0x3F , "RTMPT Basic Header chunk stream ID" , HFILL }
 }
 , {
 & hf_rtmpt_header_timestamp , {
 "Timestamp" , "rtmpt.header.timestamp" , FT_UINT24 , BASE_DEC , NULL , 0x0 , "RTMPT Message Header timestamp" , HFILL }
 }
 , {
 & hf_rtmpt_header_timestamp_delta , {
 "Timestamp delta" , "rtmpt.header.timestampdelta" , FT_UINT24 , BASE_DEC , NULL , 0x0 , "RTMPT Message Header timestamp delta" , HFILL }
 }
 , {
 & hf_rtmpt_header_body_size , {
 "Body size" , "rtmpt.header.bodysize" , FT_UINT24 , BASE_DEC , NULL , 0x0 , "RTMPT Message Header body size" , HFILL }
 }
 , {
 & hf_rtmpt_header_typeid , {
 "Type ID" , "rtmpt.header.typeid" , FT_UINT8 , BASE_HEX , VALS ( rtmpt_opcode_vals ) , 0x0 , "RTMPT Message Header type ID" , HFILL }
 }
 , {
 & hf_rtmpt_header_streamid , {
 "Stream ID" , "rtmpt.header.streamid" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "RTMPT Header stream ID" , HFILL }
 }
 , {
 & hf_rtmpt_header_ets , {
 "Extended timestamp" , "rtmpt.header.ets" , FT_UINT24 , BASE_DEC , NULL , 0x0 , "RTMPT Message Header extended timestamp" , HFILL }
 }
 , {
 & hf_rtmpt_scm_chunksize , {
 "Chunk size" , "rtmpt.scm.chunksize" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "RTMPT SCM chunk size" , HFILL }
 }
 , {
 & hf_rtmpt_scm_csid , {
 "Chunk stream ID" , "rtmpt.scm.csid" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "RTMPT SCM chunk stream ID" , HFILL }
 }
 , {
 & hf_rtmpt_scm_seq , {
 "Sequence number" , "rtmpt.scm.seq" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "RTMPT SCM acknowledgement sequence number" , HFILL }
 }
 , {
 & hf_rtmpt_scm_was , {
 "Window acknowledgement size" , "rtmpt.scm.was" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "RTMPT SCM window acknowledgement size" , HFILL }
 }
 , {
 & hf_rtmpt_scm_limittype , {
 "Limit type" , "rtmpt.scm.limittype" , FT_UINT8 , BASE_DEC , VALS ( rtmpt_limit_vals ) , 0x0 , "RTMPT SCM window acknowledgement size" , HFILL }
 }
 , {
 & hf_rtmpt_ucm_eventtype , {
 "Event type" , "rtmpt.ucm.eventtype" , FT_UINT16 , BASE_DEC , VALS ( rtmpt_ucm_vals ) , 0x0 , "RTMPT UCM event type" , HFILL }
 }
 , {
 & hf_rtmpt_function_call , {
 "Response to this call in frame" , "rtmpt.function.call" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , "RTMPT function call" , HFILL }
 }
 , {
 & hf_rtmpt_function_response , {
 "Call for this response in frame" , "rtmpt.function.response" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , "RTMPT function response" , HFILL }
 }
 , {
 & hf_rtmpt_audio_control , {
 "Audio control" , "rtmpt.audio.control" , FT_UINT8 , BASE_HEX , NULL , 0x0 , "RTMPT Audio control" , HFILL }
 }
 , {
 & hf_rtmpt_audio_format , {
 "Format" , "rtmpt.audio.format" , FT_UINT8 , BASE_DEC , VALS ( rtmpt_audio_codecs ) , 0xf0 , "RTMPT Audio format" , HFILL }
 }
 , {
 & hf_rtmpt_audio_rate , {
 "Sample rate" , "rtmpt.audio.rate" , FT_UINT8 , BASE_DEC , VALS ( rtmpt_audio_rates ) , 0x0c , "RTMPT Audio sample rate" , HFILL }
 }
 , {
 & hf_rtmpt_audio_size , {
 "Sample size" , "rtmpt.audio.size" , FT_UINT8 , BASE_DEC , VALS ( rtmpt_audio_sizes ) , 0x02 , "RTMPT Audio sample size" , HFILL }
 }
 , {
 & hf_rtmpt_audio_type , {
 "Channels" , "rtmpt.audio.type" , FT_UINT8 , BASE_DEC , VALS ( rtmpt_audio_types ) , 0x01 , "RTMPT Audio channel count" , HFILL }
 }
 , {
 & hf_rtmpt_audio_data , {
 "Audio data" , "rtmpt.audio.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , "RTMPT Audio data" , HFILL }
 }
 , {
 & hf_rtmpt_video_control , {
 "Video control" , "rtmpt.video.control" , FT_UINT8 , BASE_HEX , NULL , 0x0 , "RTMPT Video control" , HFILL }
 }
 , {
 & hf_rtmpt_video_type , {
 "Type" , "rtmpt.video.type" , FT_UINT8 , BASE_DEC , VALS ( rtmpt_video_types ) , 0xf0 , "RTMPT Video type" , HFILL }
 }
 , {
 & hf_rtmpt_video_format , {
 "Format" , "rtmpt.video.format" , FT_UINT8 , BASE_DEC , VALS ( rtmpt_video_codecs ) , 0x0f , "RTMPT Video format" , HFILL }
 }
 , {
 & hf_rtmpt_video_data , {
 "Video data" , "rtmpt.video.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , "RTMPT Video data" , HFILL }
 }
 , {
 & hf_rtmpt_tag_type , {
 "Type" , "rtmpt.tag.type" , FT_UINT8 , BASE_DEC , VALS ( rtmpt_tag_vals ) , 0x0 , "RTMPT Aggregate tag type" , HFILL }
 }
 , {
 & hf_rtmpt_tag_datasize , {
 "Data size" , "rtmpt.tag.datasize" , FT_UINT24 , BASE_DEC , NULL , 0x0 , "RTMPT Aggregate tag data size" , HFILL }
 }
 , {
 & hf_rtmpt_tag_timestamp , {
 "Timestamp" , "rtmpt.tag.timestamp" , FT_UINT24 , BASE_DEC , NULL , 0x0 , "RTMPT Aggregate tag timestamp" , HFILL }
 }
 , {
 & hf_rtmpt_tag_ets , {
 "Timestamp Extended" , "rtmpt.tag.ets" , FT_UINT8 , BASE_DEC , NULL , 0x0 , "RTMPT Aggregate tag timestamp extended" , HFILL }
 }
 , {
 & hf_rtmpt_tag_streamid , {
 "Stream ID" , "rtmpt.tag.streamid" , FT_UINT24 , BASE_DEC , NULL , 0x0 , "RTMPT Aggregate tag stream ID" , HFILL }
 }
 , {
 & hf_rtmpt_tag_tagsize , {
 "Previous tag size" , "rtmpt.tag.tagsize" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "RTMPT Aggregate previous tag size" , HFILL }
 }
 }
 ;
 static gint * ett [ ] = {
 & ett_rtmpt , & ett_rtmpt_handshake , & ett_rtmpt_header , & ett_rtmpt_body , & ett_rtmpt_ucm , & ett_rtmpt_audio_control , & ett_rtmpt_video_control , & ett_rtmpt_tag , & ett_rtmpt_tag_data }
 ;
 module_t * rtmpt_module ;
 proto_rtmpt = proto_register_protocol ( "Real Time Messaging Protocol" , "RTMPT" , "rtmpt" ) ;
 proto_register_field_array ( proto_rtmpt , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 rtmpt_module = prefs_register_protocol ( proto_rtmpt , NULL ) ;
 prefs_register_bool_preference ( rtmpt_module , "desegment" , "Reassemble RTMPT messages spanning multiple TCP segments" , "Whether the RTMPT dissector should reassemble messages spanning multiple TCP segments." " To use this option, you must also enable \"Allow subdissectors to reassemble TCP streams\"" " in the TCP protocol settings." , & rtmpt_desegment ) ;
 prefs_register_uint_preference ( rtmpt_module , "max_packet_size" , "Maximum packet size" , "The largest acceptable packet size for reassembly" , 10 , & rtmpt_max_packet_size ) ;
 }