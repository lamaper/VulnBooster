static gint dissect_codec ( tvbuff_t * tvb , packet_info * pinfo , proto_item * service_item , proto_tree * tree , gint offset , guint losc , gint media_type , gint media_codec_type , guint32 * vendor_id , guint16 * vendor_codec ) {
 proto_item * pitem ;
 guint32 value ;
 guint8 * value8 = ( guint8 * ) & value ;
 switch ( media_type ) {
 case MEDIA_TYPE_AUDIO : switch ( media_codec_type ) {
 case CODEC_SBC : proto_tree_add_item ( tree , hf_btavdtp_sbc_sampling_frequency_16000 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_sampling_frequency_32000 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_sampling_frequency_44100 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_sampling_frequency_48000 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_channel_mode_mono , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_channel_mode_dual_channel , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_channel_mode_stereo , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_channel_mode_joint_stereo , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_block_4 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_block_8 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_block_12 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_block_16 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_subbands_4 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_subbands_8 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_allocation_method_snr , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_sbc_allocation_method_loudness , tvb , offset + 1 , 1 , ENC_NA ) ;
 pitem = proto_tree_add_item ( tree , hf_btavdtp_sbc_min_bitpool , tvb , offset + 2 , 1 , ENC_NA ) ;
 value = tvb_get_guint8 ( tvb , offset + 2 ) ;
 if ( value < 2 || value > 250 ) {
 expert_add_info ( pinfo , pitem , & ei_btavdtp_sbc_min_bitpool_out_of_range ) ;
 }
 pitem = proto_tree_add_item ( tree , hf_btavdtp_sbc_max_bitpool , tvb , offset + 3 , 1 , ENC_NA ) ;
 value = tvb_get_guint8 ( tvb , offset + 3 ) ;
 if ( value < 2 || value > 250 ) {
 expert_add_info ( pinfo , pitem , & ei_btavdtp_sbc_max_bitpool_out_of_range ) ;
 }
 value = tvb_get_h_guint32 ( tvb , offset ) ;
 if ( value ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " (%s%s%s%s%s| %s%s%s%s%s| block: %s%s%s%s%s| subbands: %s%s%s| allocation: %s%s%s| bitpool: %u..%u)" , ( value8 [ 0 ] & 0x80 ) ? "16000 " : "" , ( value8 [ 0 ] & 0x40 ) ? "32000 " : "" , ( value8 [ 0 ] & 0x20 ) ? "44100 " : "" , ( value8 [ 0 ] & 0x10 ) ? "48000 " : "" , ( value8 [ 0 ] & 0xF0 ) ? "" : "not set " , ( value8 [ 0 ] & 0x08 ) ? "Mono " : "" , ( value8 [ 0 ] & 0x04 ) ? "DualChannel " : "" , ( value8 [ 0 ] & 0x02 ) ? "Stereo " : "" , ( value8 [ 0 ] & 0x01 ) ? "JointStereo " : "" , ( value8 [ 0 ] & 0x0F ) ? "" : "not set " , ( value8 [ 1 ] & 0x80 ) ? "4 " : "" , ( value8 [ 1 ] & 0x40 ) ? "8 " : "" , ( value8 [ 1 ] & 0x20 ) ? "12 " : "" , ( value8 [ 1 ] & 0x10 ) ? "16 " : "" , ( value8 [ 1 ] & 0xF0 ) ? "" : "not set " , ( value8 [ 1 ] & 0x08 ) ? "4 " : "" , ( value8 [ 1 ] & 0x04 ) ? "8 " : "" , ( value8 [ 1 ] & 0x0C ) ? "" : "not set " , ( value8 [ 1 ] & 0x02 ) ? "SNR " : "" , ( value8 [ 1 ] & 0x01 ) ? "Loudness " : "" , ( value8 [ 0 ] & 0x03 ) ? "" : "not set " , value8 [ 2 ] , value8 [ 3 ] ) ;
 proto_item_append_text ( service_item , " (%s%s%s%s%s| %s%s%s%s%s| block: %s%s%s%s%s| subbands: %s%s%s| allocation: %s%s%s| bitpool: %u..%u)" , ( value8 [ 0 ] & 0x80 ) ? "16000 " : "" , ( value8 [ 0 ] & 0x40 ) ? "32000 " : "" , ( value8 [ 0 ] & 0x20 ) ? "44100 " : "" , ( value8 [ 0 ] & 0x10 ) ? "48000 " : "" , ( value8 [ 0 ] & 0xF0 ) ? "" : "not set " , ( value8 [ 0 ] & 0x08 ) ? "Mono " : "" , ( value8 [ 0 ] & 0x04 ) ? "DualChannel " : "" , ( value8 [ 0 ] & 0x02 ) ? "Stereo " : "" , ( value8 [ 0 ] & 0x01 ) ? "JointStereo " : "" , ( value8 [ 0 ] & 0x0F ) ? "" : "not set " , ( value8 [ 1 ] & 0x80 ) ? "4 " : "" , ( value8 [ 1 ] & 0x40 ) ? "8 " : "" , ( value8 [ 1 ] & 0x20 ) ? "12 " : "" , ( value8 [ 1 ] & 0x10 ) ? "16 " : "" , ( value8 [ 1 ] & 0xF0 ) ? "" : "not set " , ( value8 [ 1 ] & 0x08 ) ? "4 " : "" , ( value8 [ 1 ] & 0x04 ) ? "8 " : "" , ( value8 [ 1 ] & 0x0C ) ? "" : "not set " , ( value8 [ 1 ] & 0x02 ) ? "SNR " : "" , ( value8 [ 1 ] & 0x01 ) ? "Loudness " : "" , ( value8 [ 0 ] & 0x03 ) ? "" : "not set " , value8 [ 2 ] , value8 [ 3 ] ) ;
 }
 else {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " (none)" ) ;
 proto_item_append_text ( service_item , " (none)" ) ;
 }
 break ;
 case CODEC_MPEG12_AUDIO : proto_tree_add_item ( tree , hf_btavdtp_mpeg12_layer_1 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_layer_2 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_layer_3 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_crc_protection , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_channel_mode_mono , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_channel_mode_dual_channel , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_channel_mode_stereo , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_channel_mode_joint_stereo , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_rfa , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_mpf_2 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_sampling_frequency_16000 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_sampling_frequency_22050 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_sampling_frequency_24000 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_sampling_frequency_32000 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_sampling_frequency_44100 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_sampling_frequency_48000 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_vbr_supported , tvb , offset + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg12_bit_rate , tvb , offset + 2 , 2 , ENC_BIG_ENDIAN ) ;
 break ;
 case CODEC_MPEG24_AAC : proto_tree_add_item ( tree , hf_btavdtp_mpeg24_object_type_mpeg2_aac_lc , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_object_type_mpeg4_aac_lc , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_object_type_mpeg4_aac_ltp , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_object_type_mpeg4_aac_scalable , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_object_type_rfa , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_8000 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_11025 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_12000 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_16000 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_22050 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_24000 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_32000 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_44100 , tvb , offset + 1 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_48000 , tvb , offset + 2 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_64000 , tvb , offset + 2 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_88200 , tvb , offset + 2 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_sampling_frequency_96000 , tvb , offset + 2 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_channels_1 , tvb , offset + 2 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_channels_2 , tvb , offset + 2 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_rfa , tvb , offset + 2 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_vbr_supported , tvb , offset + 3 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg24_bit_rate , tvb , offset + 3 , 3 , ENC_BIG_ENDIAN ) ;
 break ;
 case CODEC_ATRAC : proto_tree_add_item ( tree , hf_btavdtp_atrac_version , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_channel_mode_single_channel , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_channel_mode_dual_channel , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_channel_mode_joint_stereo , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_rfa1 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_rfa2 , tvb , offset + 1 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_sampling_frequency_44100 , tvb , offset + 1 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_sampling_frequency_48000 , tvb , offset + 1 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_vbr_supported , tvb , offset + 3 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_bit_rate , tvb , offset + 3 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_maximum_sul , tvb , offset + 4 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_atrac_rfa3 , tvb , offset + 6 , 1 , ENC_NA ) ;
 break ;
 case CODEC_VENDOR : proto_tree_add_item ( tree , hf_btavdtp_vendor_id , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 if ( vendor_id ) * vendor_id = tvb_get_letohl ( tvb , offset ) ;
 if ( vendor_codec ) * vendor_codec = tvb_get_letohs ( tvb , offset + 4 ) ;
 switch ( tvb_get_letohl ( tvb , offset ) ) {
 case 0x004F : proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_apt_codec_id , tvb , offset + 4 , 2 , ENC_LITTLE_ENDIAN ) ;
 value = tvb_get_letohs ( tvb , offset + 4 ) ;
 if ( value == 0x0001 ) {
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_aptx_sampling_frequency_16000 , tvb , offset + 6 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_aptx_sampling_frequency_32000 , tvb , offset + 6 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_aptx_sampling_frequency_44100 , tvb , offset + 6 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_aptx_sampling_frequency_48000 , tvb , offset + 6 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_aptx_channel_mode_mono , tvb , offset + 6 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_aptx_channel_mode_dual_channel , tvb , offset + 6 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_aptx_channel_mode_stereo , tvb , offset + 6 , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_aptx_channel_mode_joint_stereo , tvb , offset + 6 , 1 , ENC_NA ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " (%s -" , val_to_str_const ( value , vendor_apt_codec_vals , "unknown codec" ) ) ;
 proto_item_append_text ( service_item , " (%s -" , val_to_str_const ( value , vendor_apt_codec_vals , "unknown codec" ) ) ;
 value = tvb_get_guint8 ( tvb , offset + 6 ) ;
 if ( value ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "%s%s%s%s%s,%s%s%s%s%s)" , ( value & 0x80 ) ? " 16000" : "" , ( value & 0x40 ) ? " 32000" : "" , ( value & 0x20 ) ? " 44100" : "" , ( value & 0x10 ) ? " 48000" : "" , ( value & 0xF0 ) ? "" : "not set " , ( value & 0x08 ) ? " Mono" : "" , ( value & 0x04 ) ? " DualChannel" : "" , ( value & 0x02 ) ? " Stereo" : "" , ( value & 0x01 ) ? " JointStereo" : "" , ( value & 0x0F ) ? "" : "not set " ) ;
 proto_item_append_text ( service_item , "%s%s%s%s%s,%s%s%s%s%s)" , ( value & 0x80 ) ? " 16000" : "" , ( value & 0x40 ) ? " 32000" : "" , ( value & 0x20 ) ? " 44100" : "" , ( value & 0x10 ) ? " 48000" : "" , ( value & 0xF0 ) ? "" : "not set " , ( value & 0x08 ) ? " Mono" : "" , ( value & 0x04 ) ? " DualChannel" : "" , ( value & 0x02 ) ? " Stereo" : "" , ( value & 0x01 ) ? " JointStereo" : "" , ( value & 0x0F ) ? "" : "not set " ) ;
 }
 else {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " none)" ) ;
 proto_item_append_text ( service_item , " none)" ) ;
 }
 }
 else {
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_value , tvb , offset + 6 , losc - 6 , ENC_NA ) ;
 }
 break ;
 default : proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_codec_id , tvb , offset + 4 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_value , tvb , offset + 6 , losc - 6 , ENC_NA ) ;
 }
 break ;
 default : proto_tree_add_item ( tree , hf_btavdtp_data , tvb , offset , losc , ENC_NA ) ;
 }
 break ;
 case MEDIA_TYPE_VIDEO : switch ( media_codec_type ) {
 case CODEC_H263_BASELINE : case CODEC_H263_PROFILE_3 : case CODEC_H263_PROFILE_8 : proto_tree_add_item ( tree , hf_btavdtp_h263_level_10 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_h263_level_20 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_h263_level_30 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_h263_level_rfa , tvb , offset , 1 , ENC_NA ) ;
 break ;
 case CODEC_MPEG4_VSP : proto_tree_add_item ( tree , hf_btavdtp_mpeg4_level_0 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg4_level_1 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg4_level_2 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg4_level_3 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_btavdtp_mpeg4_level_rfa , tvb , offset , 1 , ENC_NA ) ;
 break ;
 case CODEC_VENDOR : proto_tree_add_item ( tree , hf_btavdtp_vendor_id , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_codec_id , tvb , offset + 4 , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_btavdtp_vendor_specific_value , tvb , offset + 6 , losc - 6 , ENC_NA ) ;
 break ;
 default : proto_tree_add_item ( tree , hf_btavdtp_data , tvb , offset , losc , ENC_NA ) ;
 }
 break ;
 default : proto_tree_add_item ( tree , hf_btavdtp_data , tvb , offset , losc , ENC_NA ) ;
 }
 offset += losc ;
 return offset ;
 }