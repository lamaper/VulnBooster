static gint dissect_capabilities ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gint offset , gint * codec , gint * content_protection_type , guint32 * vendor_id , guint16 * vendor_codec , guint32 * configuration_offset , guint8 * configuration_length ) {
 proto_item * pitem = NULL ;
 proto_item * ptree = NULL ;
 proto_tree * capabilities_tree ;
 proto_item * capabilities_item ;
 proto_tree * service_tree = NULL ;
 proto_item * service_item = NULL ;
 gint service_category = 0 ;
 gint losc = 0 ;
 gint recovery_type = 0 ;
 gint maximum_recovery_window_size = 0 ;
 gint maximum_number_of_media_packet_in_parity_code = 0 ;
 gint media_type = 0 ;
 gint media_codec_type = 0 ;
 capabilities_item = proto_tree_add_item ( tree , hf_btavdtp_capabilities , tvb , offset , tvb_reported_length ( tvb ) - offset , ENC_NA ) ;
 capabilities_tree = proto_item_add_subtree ( capabilities_item , ett_btavdtp_capabilities ) ;
 if ( codec ) * codec = - 1 ;
 if ( vendor_id ) * vendor_id = 0x003F ;
 if ( vendor_codec ) * vendor_codec = 0 ;
 if ( configuration_length ) * configuration_length = 0 ;
 if ( configuration_offset ) * configuration_offset = 0 ;
 while ( tvb_reported_length_remaining ( tvb , offset ) > 0 ) {
 service_category = tvb_get_guint8 ( tvb , offset ) ;
 losc = tvb_get_guint8 ( tvb , offset + 1 ) ;
 service_item = proto_tree_add_none_format ( capabilities_tree , hf_btavdtp_service , tvb , offset , 2 + losc , "Service: %s" , val_to_str_const ( service_category , service_category_vals , "RFD" ) ) ;
 service_tree = proto_item_add_subtree ( service_item , ett_btavdtp_service ) ;
 proto_tree_add_item ( service_tree , hf_btavdtp_service_category , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 proto_tree_add_item ( service_tree , hf_btavdtp_length_of_service_category , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 switch ( service_category ) {
 case SERVICE_CATEGORY_MEDIA_TRANSPORT : case SERVICE_CATEGORY_REPORTING : case SERVICE_CATEGORY_DELAY_REPORTING : break ;
 case SERVICE_CATEGORY_RECOVERY : recovery_type = tvb_get_guint8 ( tvb , offset ) ;
 pitem = proto_tree_add_item ( service_tree , hf_btavdtp_recovery_type , tvb , offset , 1 , ENC_NA ) ;
 proto_item_append_text ( pitem , " (%s)" , val_to_str_const ( recovery_type , recovery_type_vals , "RFD" ) ) ;
 offset += 1 ;
 losc -= 1 ;
 maximum_recovery_window_size = tvb_get_guint8 ( tvb , offset ) ;
 pitem = proto_tree_add_item ( service_tree , hf_btavdtp_maximum_recovery_window_size , tvb , offset , 1 , ENC_NA ) ;
 if ( maximum_recovery_window_size == 0x00 ) {
 proto_item_append_text ( pitem , " (Forbidden)" ) ;
 }
 else if ( maximum_recovery_window_size >= 0x18 ) {
 proto_item_append_text ( pitem , " (Undocumented)" ) ;
 }
 offset += 1 ;
 losc -= 1 ;
 maximum_number_of_media_packet_in_parity_code = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( service_tree , hf_btavdtp_maximum_number_of_media_packet_in_parity_code , tvb , offset , 1 , ENC_NA ) ;
 pitem = proto_tree_add_item ( service_tree , hf_btavdtp_maximum_recovery_window_size , tvb , offset , 1 , ENC_NA ) ;
 if ( maximum_number_of_media_packet_in_parity_code == 0x00 ) {
 proto_item_append_text ( pitem , " (Forbidden)" ) ;
 }
 else if ( maximum_number_of_media_packet_in_parity_code >= 0x18 ) {
 proto_item_append_text ( pitem , " (Undocumented)" ) ;
 }
 offset += 1 ;
 losc -= 1 ;
 break ;
 case SERVICE_CATEGORY_MEDIA_CODEC : if ( configuration_length ) * configuration_length = losc ;
 if ( configuration_offset ) * configuration_offset = offset ;
 media_type = tvb_get_guint8 ( tvb , offset ) >> 4 ;
 proto_tree_add_item ( service_tree , hf_btavdtp_media_codec_media_type , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( service_tree , hf_btavdtp_media_codec_rfa , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 losc -= 1 ;
 media_codec_type = tvb_get_guint8 ( tvb , offset ) ;
 if ( codec ) {
 * codec = media_codec_type ;
 }
 if ( media_type == MEDIA_TYPE_AUDIO ) {
 proto_tree_add_item ( service_tree , hf_btavdtp_media_codec_audio_type , tvb , offset , 1 , ENC_NA ) ;
 proto_item_append_text ( service_item , " - Audio %s" , val_to_str_const ( media_codec_type , media_codec_audio_type_vals , "unknown codec" ) ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " - Audio %s" , val_to_str_const ( media_codec_type , media_codec_audio_type_vals , "unknown codec" ) ) ;
 }
 else if ( media_type == MEDIA_TYPE_VIDEO ) {
 proto_tree_add_item ( service_tree , hf_btavdtp_media_codec_video_type , tvb , offset , 1 , ENC_NA ) ;
 proto_item_append_text ( service_item , " - Video %s" , val_to_str_const ( media_codec_type , media_codec_video_type_vals , "unknown codec" ) ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " - Video %s" , val_to_str_const ( media_codec_type , media_codec_video_type_vals , "unknown codec" ) ) ;
 }
 else {
 proto_tree_add_item ( service_tree , hf_btavdtp_media_codec_unknown_type , tvb , offset , 1 , ENC_NA ) ;
 proto_item_append_text ( service_item , " - Unknown 0x%02x" , media_codec_type ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " - Unknown 0x%02x" , media_codec_type ) ;
 }
 offset += 1 ;
 losc -= 1 ;
 offset = dissect_codec ( tvb , pinfo , service_item , service_tree , offset , losc , media_type , media_codec_type , vendor_id , vendor_codec ) ;
 losc = 0 ;
 break ;
 case SERVICE_CATEGORY_CONTENT_PROTECTION : proto_tree_add_item ( service_tree , hf_btavdtp_content_protection_type , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 if ( content_protection_type ) {
 * content_protection_type = tvb_get_letohs ( tvb , offset ) ;
 }
 proto_item_append_text ( service_item , " - %s" , val_to_str_const ( tvb_get_letohs ( tvb , offset ) , content_protection_type_vals , "unknown" ) ) ;
 offset += 2 ;
 losc -= 2 ;
 if ( losc > 0 ) {
 proto_tree_add_item ( service_tree , hf_btavdtp_data , tvb , offset , losc , ENC_NA ) ;
 offset += losc ;
 losc = 0 ;
 }
 break ;
 case SERVICE_CATEGORY_HEADER_COMPRESSION : proto_tree_add_item ( service_tree , hf_btavdtp_header_compression_backch , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( service_tree , hf_btavdtp_header_compression_media , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( service_tree , hf_btavdtp_header_compression_recovery , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( service_tree , hf_btavdtp_header_compression_rfa , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 losc -= 1 ;
 break ;
 case SERVICE_CATEGORY_MULTIPLEXING : proto_tree_add_item ( service_tree , hf_btavdtp_multiplexing_fragmentation , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( service_tree , hf_btavdtp_multiplexing_rfa , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 losc -= 1 ;
 if ( losc >= 2 ) {
 pitem = proto_tree_add_none_format ( service_tree , hf_btavdtp_service_multiplexing_entry , tvb , offset , 1 + losc , "Entry: Media Transport Session" ) ;
 ptree = proto_item_add_subtree ( pitem , ett_btavdtp_service ) ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_tsid , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_entry_rfa , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 losc -= 1 ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_tcid , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_entry_rfa , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 losc -= 1 ;
 }
 if ( losc >= 2 ) {
 pitem = proto_tree_add_none_format ( service_tree , hf_btavdtp_service_multiplexing_entry , tvb , offset , 1 + losc , "Entry: Reporting Transport Session" ) ;
 ptree = proto_item_add_subtree ( pitem , ett_btavdtp_service ) ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_tsid , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_entry_rfa , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 losc -= 1 ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_tcid , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_entry_rfa , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 losc -= 1 ;
 }
 if ( losc >= 2 ) {
 pitem = proto_tree_add_none_format ( service_tree , hf_btavdtp_service_multiplexing_entry , tvb , offset , 1 + losc , "Entry: Recovery Transport Session" ) ;
 ptree = proto_item_add_subtree ( pitem , ett_btavdtp_service ) ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_tsid , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_entry_rfa , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 losc -= 1 ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_tcid , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( ptree , hf_btavdtp_multiplexing_entry_rfa , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 losc -= 1 ;
 }
 break ;
 default : proto_tree_add_item ( service_tree , hf_btavdtp_data , tvb , offset , losc , ENC_NA ) ;
 offset += losc ;
 losc = 0 ;
 }
 if ( losc > 0 ) {
 pitem = proto_tree_add_item ( service_tree , hf_btavdtp_data , tvb , offset , losc , ENC_NA ) ;
 offset += losc ;
 expert_add_info ( pinfo , pitem , & ei_btavdtp_unexpected_losc_data ) ;
 }
 }
 return offset ;
 }