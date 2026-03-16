static gint dissect_btvdp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_item * ti ;
 proto_tree * btvdp_tree ;
 proto_item * pitem ;
 gint offset = 0 ;
 dissector_handle_t codec_dissector = NULL ;
 btvdp_codec_info_t btvdp_codec_info ;
 sep_data_t sep_data ;
 gboolean no_avdtp_session ;
 no_avdtp_session = ( proto_btavdtp != ( gint ) GPOINTER_TO_UINT ( wmem_list_frame_data ( wmem_list_frame_prev ( wmem_list_tail ( pinfo -> layers ) ) ) ) ) ;
 sep_data . codec = CODEC_H263_BASELINE ;
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
 if ( force_vdp_scms_t || force_vdp_codec ) {
 if ( force_vdp_scms_t ) sep_data . content_protection_type = 2 ;
 else if ( data && ! no_avdtp_session ) sep_data . content_protection_type = ( ( sep_data_t * ) data ) -> content_protection_type ;
 if ( force_vdp_codec ) sep_data . codec = force_vdp_codec ;
 else if ( data && ! no_avdtp_session ) sep_data . codec = ( ( sep_data_t * ) data ) -> codec ;
 }
 else {
 if ( data && ! no_avdtp_session ) sep_data = * ( ( sep_data_t * ) data ) ;
 }
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "VDP" ) ;
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
 ti = proto_tree_add_item ( tree , proto_btvdp , tvb , offset , - 1 , ENC_NA ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "Video stream - %s" , val_to_str_const ( sep_data . codec , media_codec_video_type_vals , "unknown codec" ) ) ;
 btvdp_tree = proto_item_add_subtree ( ti , ett_btvdp ) ;
 pitem = proto_tree_add_uint ( btvdp_tree , hf_btvdp_acp_seid , tvb , 0 , 0 , sep_data . acp_seid ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 pitem = proto_tree_add_uint ( btvdp_tree , hf_btvdp_int_seid , tvb , 0 , 0 , sep_data . int_seid ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 pitem = proto_tree_add_uint ( btvdp_tree , hf_btvdp_codec , tvb , 0 , 0 , sep_data . codec ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 if ( sep_data . codec == 0xFF ) {
 pitem = proto_tree_add_uint ( btvdp_tree , hf_btvdp_vendor_id , tvb , 0 , 0 , sep_data . vendor_id ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 pitem = proto_tree_add_uint ( btvdp_tree , hf_btvdp_vendor_codec_id , tvb , 0 , 0 , sep_data . vendor_codec ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 }
 if ( sep_data . content_protection_type > 0 ) {
 pitem = proto_tree_add_uint ( btvdp_tree , hf_btvdp_content_protection , tvb , 0 , 0 , sep_data . content_protection_type ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 }
 if ( sep_data . stream_start_in_frame > 0 ) {
 pitem = proto_tree_add_uint ( btvdp_tree , hf_btvdp_stream_start_in_frame , tvb , 0 , 0 , sep_data . stream_start_in_frame ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 }
 if ( sep_data . stream_end_in_frame > 0 ) {
 pitem = proto_tree_add_uint ( btvdp_tree , hf_btvdp_stream_end_in_frame , tvb , 0 , 0 , sep_data . stream_end_in_frame ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 }
 pitem = proto_tree_add_uint ( btvdp_tree , hf_btvdp_stream_number , tvb , 0 , 0 , sep_data . stream_number ) ;
 PROTO_ITEM_SET_GENERATED ( pitem ) ;
 switch ( sep_data . codec ) {
 case CODEC_H263_BASELINE : case CODEC_H263_PROFILE_3 : case CODEC_H263_PROFILE_8 : codec_dissector = h263_handle ;
 break ;
 case CODEC_MPEG4_VSP : codec_dissector = mp4v_es_handle ;
 break ;
 }
 btvdp_codec_info . codec_dissector = codec_dissector ;
 btvdp_codec_info . content_protection_type = sep_data . content_protection_type ;

 pinfo -> destport = sep_data . stream_number ;

 call_dissector ( rtp_handle , tvb , pinfo , tree ) ;
 offset += tvb_reported_length_remaining ( tvb , offset ) ;
 return offset ;
 }