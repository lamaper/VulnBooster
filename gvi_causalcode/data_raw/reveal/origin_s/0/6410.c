static gint dissect_bta2dp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_item * ti ;
 proto_tree * bta2dp_tree ;
 proto_item * pitem ;
 gint offset = 0 ;
 dissector_handle_t codec_dissector = NULL ;
 bta2dp_codec_info_t bta2dp_codec_info ;
 sep_data_t sep_data ;
 gboolean no_avdtp_session ;
 no_avdtp_session = ( proto_btavdtp != ( gint ) GPOINTER_TO_UINT ( wmem_list_frame_data ( wmem_list_frame_prev ( wmem_list_tail ( pinfo -> layers ) ) ) ) ) ;
 sep_data . codec = CODEC_SBC ;
 sep_data . content_protection_type = 0 ;
 sep_data . acp_seid = 0 ;
 sep_data . int_seid = 0 ;
 sep_data . previous_media_packet_info = NULL ;
 sep_data . current_media_packet_info = NULL ;
 sep_data . stream_start_in_frame = 0 ;
 sep_data . stream_end_in_frame = 0 ;
 sep_data . stream_number = 1 ;
 sep_data . vendor_id = 0 ;
 sep_data . vendor_codec = 0 ;
 sep_data . configuration_length = 0 ;
 sep_data . configuration = NULL ;
 if ( force_a2dp_scms_t || force_a2dp_codec != CODEC_DEFAULT ) {
 if ( force_a2dp_scms_t ) sep_data . content_protection_type = 2 ;
 else if ( data && ! no_avdtp_session ) sep_data . content_protection_type = ( ( sep_data_t * ) data ) -> content_protection_type ;
 if ( force_a2dp_codec != CODEC_DEFAULT ) sep_data . codec = force_a2dp_codec ;
 else if ( data && ! no_avdtp_session ) sep_data . codec = ( ( sep_data_t * ) data ) -> codec ;
 }
 else {
 if ( data && ! no_avdtp_session ) sep_data = * ( ( sep_data_t * ) data ) ;
 }
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "A2DP" ) ;
 switch ( pinfo -> p2p_dir ) {
 case P2P_DIR_SENT : col_set_str ( pinfo -> cinfo , COL_INFO , "Sent " ) ;
 break ;
 case P2P_DIR_RECV : col_set_str ( pinfo -> cinfo , COL_INFO , "Rcvd " ) ;
 break ;
 case P2P_DIR_UNKNOWN : col_clear ( pinfo -> cinfo , COL_INFO ) ;
 break ;
 default : col_add_fstr ( pinfo -> cinfo , COL_INFO , "Unknown direction %d " , pinfo -> p2p_dir ) ;
 break ;
 }
 ti = proto_tree_add_item ( tree , proto_bta2dp , tvb , offset , - 1 , ENC_NA ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "Audio stream - %s" , val_to_str_const ( sep_data . codec , media_codec_audio_type_vals , "unknown codec" ) ) ;
 bta2dp_tree = proto_item_add_subtree ( ti , ett_bta2dp ) ;
 pitem = proto_tree_add_uint ( bta2dp_tree , hf_bta2dp_acp_seid , tvb , 0 , 0 , sep_data . acp_seid ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 pitem = proto_tree_add_uint ( bta2dp_tree , hf_bta2dp_int_seid , tvb , 0 , 0 , sep_data . int_seid ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 pitem = proto_tree_add_uint ( bta2dp_tree , hf_bta2dp_codec , tvb , 0 , 0 , sep_data . codec ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 if ( sep_data . codec == 0xFF ) {
 pitem = proto_tree_add_uint ( bta2dp_tree , hf_bta2dp_vendor_id , tvb , 0 , 0 , sep_data . vendor_id ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 pitem = proto_tree_add_uint ( bta2dp_tree , hf_bta2dp_vendor_codec_id , tvb , 0 , 0 , sep_data . vendor_codec ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 if ( sep_data . vendor_id == 0x004F && sep_data . vendor_codec == 0x0001 ) codec_dissector = aptx_handle ;
 }
 if ( sep_data . content_protection_type > 0 ) {
 pitem = proto_tree_add_uint ( bta2dp_tree , hf_bta2dp_content_protection , tvb , 0 , 0 , sep_data . content_protection_type ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 }
 if ( sep_data . stream_start_in_frame > 0 ) {
 pitem = proto_tree_add_uint ( bta2dp_tree , hf_bta2dp_stream_start_in_frame , tvb , 0 , 0 , sep_data . stream_start_in_frame ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 }
 if ( sep_data . stream_end_in_frame > 0 ) {
 pitem = proto_tree_add_uint ( bta2dp_tree , hf_bta2dp_stream_end_in_frame , tvb , 0 , 0 , sep_data . stream_end_in_frame ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 }
 pitem = proto_tree_add_uint ( bta2dp_tree , hf_bta2dp_stream_number , tvb , 0 , 0 , sep_data . stream_number ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 switch ( sep_data . codec ) {
 case CODEC_SBC : codec_dissector = sbc_handle ;
 break ;
 case CODEC_MPEG12_AUDIO : codec_dissector = mp2t_handle ;
 break ;
 case CODEC_MPEG24_AAC : codec_dissector = mpeg_audio_handle ;
 break ;
 case CODEC_ATRAC : codec_dissector = atrac_handle ;
 break ;
 case CODEC_APT_X : codec_dissector = aptx_handle ;
 break ;
 }
 bta2dp_codec_info . codec_dissector = codec_dissector ;
 bta2dp_codec_info . configuration_length = sep_data . configuration_length ;
 bta2dp_codec_info . configuration = sep_data . configuration ;
 bta2dp_codec_info . content_protection_type = sep_data . content_protection_type ;
 bta2dp_codec_info . previous_media_packet_info = sep_data . previous_media_packet_info ;
 bta2dp_codec_info . current_media_packet_info = sep_data . current_media_packet_info ;

 pinfo -> destport = sep_data . stream_number ;

 call_dissector_with_data ( aptx_handle , tvb , pinfo , tree , & bta2dp_codec_info ) ;
 }
 else {
 bluetooth_add_address ( pinfo , & pinfo -> net_dst , sep_data . stream_number , "BT A2DP" , pinfo -> num , RTP_MEDIA_AUDIO , & bta2dp_codec_info ) ;
 call_dissector ( rtp_handle , tvb , pinfo , tree ) ;
 }
 offset += tvb_reported_length_remaining ( tvb , offset ) ;
 return offset ;
 }