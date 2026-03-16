void proto_register_btavdtp ( void ) {
 module_t * module ;
 static hf_register_info hf [ ] = {
 {
 & hf_btavdtp_signal , {
 "Signal" , "btavdtp.signal" , FT_NONE , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_message_type , {
 "Message Type" , "btavdtp.message_type" , FT_UINT8 , BASE_HEX , VALS ( message_type_vals ) , AVDTP_MESSAGE_TYPE_MASK , NULL , HFILL }
 }
 , {
 & hf_btavdtp_packet_type , {
 "Packet Type" , "btavdtp.packet_type" , FT_UINT8 , BASE_HEX , VALS ( packet_type_vals ) , AVDTP_PACKET_TYPE_MASK , NULL , HFILL }
 }
 , {
 & hf_btavdtp_transaction , {
 "Transaction" , "btavdtp.transaction" , FT_UINT8 , BASE_HEX , NULL , AVDTP_TRANSACTION_MASK , NULL , HFILL }
 }
 , {
 & hf_btavdtp_signal_id , {
 "Signal" , "btavdtp.signal_id" , FT_UINT8 , BASE_HEX , VALS ( signal_id_vals ) , AVDTP_SIGNAL_ID_MASK , NULL , HFILL }
 }
 , {
 & hf_btavdtp_rfa0 , {
 "RFA" , "btavdtp.rfa0" , FT_UINT8 , BASE_HEX , NULL , AVDTP_RFA0_MASK , NULL , HFILL }
 }
 , {
 & hf_btavdtp_number_of_signal_packets , {
 "Number of signal packets" , "btavdtp.num_signal_packets" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_error_code , {
 "Error Code" , "btavdtp.error_code" , FT_UINT8 , BASE_HEX , VALS ( error_code_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sep_seid , {
 "SEID" , "btavdtp.sep_seid" , FT_UINT8 , BASE_DEC , NULL , 0xFC , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sep_inuse , {
 "In Use" , "btavdtp.sep_inuse" , FT_UINT8 , BASE_HEX , VALS ( true_false ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sep_rfa0 , {
 "RFA0" , "btavdtp.sep_rfa0" , FT_UINT8 , BASE_HEX , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sep_media_type , {
 "Media Type" , "btavdtp.sep_media_type" , FT_UINT8 , BASE_HEX , VALS ( media_type_vals ) , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sep_type , {
 "Type" , "btavdtp.sep_type" , FT_UINT8 , BASE_HEX , VALS ( sep_type_vals ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sep_rfa1 , {
 "RFA1" , "btavdtp.sep_rfa1" , FT_UINT8 , BASE_HEX , NULL , 0x07 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_acp_sep , {
 "ACP SEP" , "btavdtp.acp_sep" , FT_NONE , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_acp_seid_item , {
 "ACP SEID" , "btavdtp.acp_seid_item" , FT_NONE , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_int_seid_item , {
 "INT SEID" , "btavdtp.int_seid_item" , FT_NONE , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_acp_seid , {
 "ACP SEID" , "btavdtp.acp_seid" , FT_UINT8 , BASE_DEC , NULL , 0xFC , NULL , HFILL }
 }
 , {
 & hf_btavdtp_int_seid , {
 "INT SEID" , "btavdtp.int_seid" , FT_UINT8 , BASE_DEC , NULL , 0xFC , NULL , HFILL }
 }
 , {
 & hf_btavdtp_rfa_seid , {
 "RFA" , "btavdtp.rfa_seid" , FT_UINT8 , BASE_HEX , NULL , 0x03 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_service_category , {
 "Service Category" , "btavdtp.service_category" , FT_UINT8 , BASE_HEX , VALS ( service_category_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_length_of_service_category , {
 "Length of Service Category" , "btavdtp.length_of_service_category" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_delay , {
 "Delay" , "btavdtp.delay" , FT_UINT16 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_recovery_type , {
 "Service Category" , "btavdtp.recovery_type" , FT_UINT8 , BASE_HEX , VALS ( recovery_type_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_maximum_recovery_window_size , {
 "Service Category" , "btavdtp.maximum_recovery_window_size" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_maximum_number_of_media_packet_in_parity_code , {
 "Service Category" , "btavdtp.maximum_number_of_media_packet_in_parity_code" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_multiplexing_fragmentation , {
 "Fragmentation" , "btavdtp.multiplexing_fragmentation" , FT_UINT8 , BASE_HEX , VALS ( true_false ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_multiplexing_rfa , {
 "RFA" , "btavdtp.multiplexing_rfa" , FT_UINT8 , BASE_HEX , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_btavdtp_multiplexing_tsid , {
 "TSID" , "btavdtp.multiplexing_tsid" , FT_UINT8 , BASE_HEX , VALS ( multiplexing_tsid_vals ) , 0xF8 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_multiplexing_tcid , {
 "TCID" , "btavdtp.multiplexing_tcid" , FT_UINT8 , BASE_HEX , VALS ( multiplexing_tcid_vals ) , 0xF8 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_multiplexing_entry_rfa , {
 "RFA" , "btavdtp.multiplexing_entry_rfa" , FT_UINT8 , BASE_HEX , NULL , 0x07 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_header_compression_backch , {
 "BackCh" , "btavdtp.header_compression_backch" , FT_UINT8 , BASE_HEX , VALS ( true_false ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_header_compression_media , {
 "Media" , "btavdtp.header_compression_media" , FT_UINT8 , BASE_HEX , VALS ( true_false ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_header_compression_recovery , {
 "Recovery" , "btavdtp.header_compression_recovery" , FT_UINT8 , BASE_HEX , VALS ( true_false ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_header_compression_rfa , {
 "RFA" , "btavdtp.header_compression_rfa" , FT_UINT8 , BASE_HEX , NULL , 0x1f , NULL , HFILL }
 }
 , {
 & hf_btavdtp_content_protection_type , {
 "Type" , "btavdtp.content_protection_type" , FT_UINT16 , BASE_HEX , VALS ( content_protection_type_vals ) , 0x0000 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_media_codec_media_type , {
 "Media Type" , "btavdtp.media_codec_media_type" , FT_UINT8 , BASE_HEX , VALS ( media_type_vals ) , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_media_codec_rfa , {
 "RFA" , "btavdtp.media_codec_rfa" , FT_UINT8 , BASE_HEX , NULL , 0x0F , NULL , HFILL }
 }
 , {
 & hf_btavdtp_media_codec_audio_type , {
 "Media Codec Audio Type" , "btavdtp.media_codec_audio_type" , FT_UINT8 , BASE_HEX , VALS ( media_codec_audio_type_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_media_codec_video_type , {
 "Media Codec Video Type" , "btavdtp.media_codec_video_type" , FT_UINT8 , BASE_HEX , VALS ( media_codec_video_type_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_media_codec_unknown_type , {
 "Media Codec Unknown Type" , "btavdtp.media_codec_unknown_type" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_sampling_frequency_16000 , {
 "Sampling Frequency 16000 Hz" , "btavdtp.codec.sbc.sampling_frequency.16000" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_sampling_frequency_32000 , {
 "Sampling Frequency 32000 Hz" , "btavdtp.codec.sbc.sampling_frequency.32000" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_sampling_frequency_44100 , {
 "Sampling Frequency 44100 Hz" , "btavdtp.codec.sbc.sampling_frequency.44100" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_sampling_frequency_48000 , {
 "Sampling Frequency 48000 Hz" , "btavdtp.codec.sbc.sampling_frequency.48000" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_channel_mode_mono , {
 "Channel Mode Mono" , "btavdtp.codec.sbc.channel_mode.mono" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_channel_mode_dual_channel , {
 "Channel Mode Dual Channel" , "btavdtp.codec.sbc.channel_mode.dual_channel" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_channel_mode_stereo , {
 "Channel Mode Stereo" , "btavdtp.codec.sbc.channel_mode.stereo" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_channel_mode_joint_stereo , {
 "Channel Mode Joint Stereo" , "btavdtp.codec.sbc.channel_mode.joint_stereo" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_block_4 , {
 "Block Length 4" , "btavdtp.codec.sbc.block.4" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_block_8 , {
 "Block Length 8" , "btavdtp.codec.sbc.block.8" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_block_12 , {
 "Block Length 12" , "btavdtp.codec.sbc.block.12" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_block_16 , {
 "Block Length 16" , "btavdtp.codec.sbc.block.16" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_subbands_4 , {
 "Subbands 4" , "btavdtp.codec.sbc.subbands.4" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_subbands_8 , {
 "Subbands 8" , "btavdtp.codec.sbc.subbands.8" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_allocation_method_snr , {
 "Allocation Method SNR" , "btavdtp.codec.sbc.allocation_method.snr" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_allocation_method_loudness , {
 "Allocation Method Loudness" , "btavdtp.codec.sbc.allocation_method.loudness" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_min_bitpool , {
 "Minimum Bitpool" , "btavdtp.codec.sbc.minimum_bitpool" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_sbc_max_bitpool , {
 "Maximum Bitpool" , "btavdtp.codec.sbc.maximum_bitpool" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_layer_1 , {
 "MP1" , "btavdtp.codec.mpeg12.layer_1" , FT_BOOLEAN , 8 , NULL , 0x80 , "MPEG Layer 1" , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_layer_2 , {
 "MP2" , "btavdtp.codec.mpeg12.layer_2" , FT_BOOLEAN , 8 , NULL , 0x40 , "MPEG Layer 2" , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_layer_3 , {
 "MP3" , "btavdtp.codec.mpeg12.layer_3" , FT_BOOLEAN , 8 , NULL , 0x20 , "MPEG Layer 3" , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_crc_protection , {
 "CRC Protection" , "btavdtp.codec.mpeg12.crc_protection" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_channel_mode_mono , {
 "Channel Mode Mono" , "btavdtp.codec.mpeg12.channel_mode.mono" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_channel_mode_dual_channel , {
 "Channel Mode Dual Channel" , "btavdtp.codec.mpeg12.channel_mode.dual_channel" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_channel_mode_stereo , {
 "Channel Mode Stereo" , "btavdtp.codec.mpeg12.channel_mode.stereo" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_channel_mode_joint_stereo , {
 "Channel Mode Joint Stereo" , "btavdtp.codec.mpeg12.channel_mode.joint_stereo" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_rfa , {
 "RFA" , "btavdtp.codec.mpeg12.rfa" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_mpf_2 , {
 "Media Payload Format 2" , "btavdtp.codec.mpeg12.mpf_2" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_sampling_frequency_16000 , {
 "Sampling Frequency 16000 Hz" , "btavdtp.codec.sbc.sampling_frequency.16000" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_sampling_frequency_22050 , {
 "Sampling Frequency 22050 Hz" , "btavdtp.codec.sbc.sampling_frequency.22050" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_sampling_frequency_24000 , {
 "Sampling Frequency 24000 Hz" , "btavdtp.codec.sbc.sampling_frequency.24000" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_sampling_frequency_32000 , {
 "Sampling Frequency 32000 Hz" , "btavdtp.codec.sbc.sampling_frequency.32000" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_sampling_frequency_44100 , {
 "Sampling Frequency 44100 Hz" , "btavdtp.codec.sbc.sampling_frequency.44100" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_sampling_frequency_48000 , {
 "Sampling Frequency 48000 Hz" , "btavdtp.codec.sbc.sampling_frequency.48000" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_vbr_supported , {
 "VBR Supported" , "btavdtp.codec.mpeg12.vbr" , FT_BOOLEAN , 16 , NULL , 0x8000 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg12_bit_rate , {
 "Bit Rate" , "btavdtp.codec.mpeg12.bit_rate" , FT_UINT16 , BASE_HEX , NULL , 0x7FFF , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_object_type_mpeg2_aac_lc , {
 "MPEG2 AAC LC" , "btavdtp.codec.mpeg24.object_type.mpeg2_aac_lc" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_object_type_mpeg4_aac_lc , {
 "MPEG4 AAC LC" , "btavdtp.codec.mpeg24.object_type.mpeg4_aac_lc" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_object_type_mpeg4_aac_ltp , {
 "MPEG4 AAC LTP" , "btavdtp.codec.mpeg24.object_type.mpeg4_aac_ltp" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_object_type_mpeg4_aac_scalable , {
 "MPEG4 AAC Scalable" , "btavdtp.codec.mpeg24.object_type.mpeg4_aac_scalable" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_object_type_rfa , {
 "RFA" , "btavdtp.codec.mpeg24.object_type.rfa" , FT_UINT8 , BASE_HEX , NULL , 0x0F , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_8000 , {
 "Sampling Frequency 8000 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.8000" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_11025 , {
 "Sampling Frequency 11025 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.11025" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_12000 , {
 "Sampling Frequency 12000 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.12000" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_16000 , {
 "Sampling Frequency 16000 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.16000" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_22050 , {
 "Sampling Frequency 22050 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.22050" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_24000 , {
 "Sampling Frequency 24000 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.24000" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_32000 , {
 "Sampling Frequency 32000 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.32000" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_44100 , {
 "Sampling Frequency 44100 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.44100" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_48000 , {
 "Sampling Frequency 48000 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.48000" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_64000 , {
 "Sampling Frequency 64000 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.64000" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_88200 , {
 "Sampling Frequency 88200 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.88200" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_sampling_frequency_96000 , {
 "Sampling Frequency 96000 Hz" , "btavdtp.codec.mpeg24.sampling_frequency.96000" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_channels_1 , {
 "Channels 1" , "btavdtp.codec.mpeg24.channels.1" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_channels_2 , {
 "Channels 2" , "btavdtp.codec.mpeg24.channels.2" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_rfa , {
 "RFA" , "btavdtp.codec.mpeg24.rfa" , FT_UINT8 , BASE_HEX , NULL , 0x03 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_vbr_supported , {
 "VBR Supported" , "btavdtp.codec.mpeg24.vbr" , FT_BOOLEAN , 24 , NULL , 0x800000 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg24_bit_rate , {
 "Bit Rate" , "btavdtp.codec.mpeg24.bit_rate" , FT_UINT24 , BASE_HEX , NULL , 0x7FFFFF , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_version , {
 "Version" , "btavdtp.codec.atrac.version" , FT_UINT8 , BASE_DEC , NULL , 0xE0 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_channel_mode_single_channel , {
 "Channel Mode Single Channel" , "btavdtp.codec.atrac.channel_mode.single_channel" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_channel_mode_dual_channel , {
 "Channel Mode Dual Channel" , "btavdtp.codec.atrac.channel_mode.dual_channel" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_channel_mode_joint_stereo , {
 "Channel Mode Joint Stereo" , "btavdtp.codec.atrac.channel_mode.joint_stereo" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_rfa1 , {
 "RFA" , "btavdtp.codec.atrac.rfa1" , FT_UINT8 , BASE_HEX , NULL , 0x03 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_rfa2 , {
 "RFA" , "btavdtp.codec.atrac.rfa2" , FT_UINT24 , BASE_HEX , NULL , 0xC00000 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_sampling_frequency_44100 , {
 "Sampling Frequency 44100 Hz" , "btavdtp.codec.sbc.sampling_frequency.44100" , FT_BOOLEAN , 24 , NULL , 0x200000 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_sampling_frequency_48000 , {
 "Sampling Frequency 48000 Hz" , "btavdtp.codec.sbc.sampling_frequency.48000" , FT_BOOLEAN , 24 , NULL , 0x100000 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_vbr_supported , {
 "VBR Supported" , "btavdtp.codec.atrac.vbr" , FT_BOOLEAN , 24 , NULL , 0x080000 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_bit_rate , {
 "Bit Rate" , "btavdtp.codec.atrac.bit_rate" , FT_UINT24 , BASE_HEX , NULL , 0x07FFFF , NULL , HFILL }
 }
 , {
 & hf_btavdtp_atrac_maximum_sul , {
 "Maximum SUL" , "btavdtp.codec.atrac.maximum_sul" , FT_UINT8 , BASE_DEC , NULL , 0x00 , "Sound Unit Length (SUL) is one of the parameters that determine bit rate of the audio stream." , HFILL }
 }
 , {
 & hf_btavdtp_atrac_rfa3 , {
 "RFA" , "btavdtp.codec.atrac.rfa3" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_h263_level_10 , {
 "H264 Level 10" , "btavdtp.codec.h264.level.10" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_h263_level_20 , {
 "H264 Level 20" , "btavdtp.codec.h264.level.20" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_h263_level_30 , {
 "H264 Level 30" , "btavdtp.codec.h264.level.30" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_h263_level_rfa , {
 "H264 Level RFA" , "btavdtp.codec.h264.level.rfa" , FT_UINT8 , BASE_HEX , NULL , 0x1F , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg4_level_0 , {
 "MPEG Level 0" , "btavdtp.codec.mpeg4.level.0" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg4_level_1 , {
 "MPEG Level 1" , "btavdtp.codec.mpeg4.level.1" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg4_level_2 , {
 "MPEG Level 2" , "btavdtp.codec.mpeg4.level.2" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg4_level_3 , {
 "MPEG4 Level 3" , "btavdtp.codec.mpeg4.level.3" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_mpeg4_level_rfa , {
 "MPEG4 Level RFA" , "btavdtp.codec.mpeg4.level.rfa" , FT_UINT8 , BASE_HEX , NULL , 0x0F , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_id , {
 "Vendor ID" , "btavdtp.codec.vendor.vendor_id" , FT_UINT32 , BASE_HEX | BASE_EXT_STRING , & bluetooth_company_id_vals_ext , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_codec_id , {
 "Codec" , "btavdtp.codec.vendor.codec_id" , FT_UINT16 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_value , {
 "Value" , "btavdtp.codec.vendor.value" , FT_NONE , BASE_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_apt_codec_id , {
 "Codec" , "btavdtp.codec.vendor.codec_id" , FT_UINT16 , BASE_HEX , VALS ( vendor_apt_codec_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_aptx_sampling_frequency_16000 , {
 "Sampling Frequency 16000 Hz" , "btavdtp.codec.aptx.sampling_frequency.16000" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_aptx_sampling_frequency_32000 , {
 "Sampling Frequency 32000 Hz" , "btavdtp.codec.aptx.sampling_frequency.32000" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_aptx_sampling_frequency_44100 , {
 "Sampling Frequency 44100 Hz" , "btavdtp.codec.aptx.sampling_frequency.44100" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_aptx_sampling_frequency_48000 , {
 "Sampling Frequency 48000 Hz" , "btavdtp.codec.aptx.sampling_frequency.48000" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_aptx_channel_mode_mono , {
 "Channel Mode Mono" , "btavdtp.codec.aptx.channel_mode.mono" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_aptx_channel_mode_dual_channel , {
 "Channel Mode Dual Channel" , "btavdtp.codec.aptx.channel_mode.dual_channel" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_aptx_channel_mode_stereo , {
 "Channel Mode Stereo" , "btavdtp.codec.aptx.channel_mode.stereo" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_vendor_specific_aptx_channel_mode_joint_stereo , {
 "Channel Mode Joint Stereo" , "btavdtp.codec.aptx.channel_mode.joint_stereo" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_capabilities , {
 "Capabilities" , "btavdtp.capabilities" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_service , {
 "Service" , "btavdtp.service" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_service_multiplexing_entry , {
 "Entry" , "btavdtp.service_multiplexing_entry" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_btavdtp_data , {
 "Data" , "btavdtp.data" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ] = {
 & ett_btavdtp , & ett_btavdtp_sep , & ett_btavdtp_capabilities , & ett_btavdtp_service , }
 ;
 proto_btavdtp = proto_register_protocol ( "Bluetooth AVDTP Protocol" , "BT AVDTP" , "btavdtp" ) ;
 btavdtp_handle = register_dissector ( "btavdtp" , dissect_btavdtp , proto_btavdtp ) ;
 proto_register_field_array ( proto_btavdtp , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 module = prefs_register_protocol_subtree ( "Bluetooth" , proto_btavdtp , NULL ) ;
 prefs_register_static_text_preference ( module , "avdtp.version" , "Bluetooth Protocol AVDTP version: 1.3" , "Version of protocol supported by this dissector." ) ;
 channels = wmem_tree_new_autoreset ( wmem_epan_scope ( ) , wmem_file_scope ( ) ) ;
 sep_list = wmem_tree_new_autoreset ( wmem_epan_scope ( ) , wmem_file_scope ( ) ) ;
 sep_open = wmem_tree_new_autoreset ( wmem_epan_scope ( ) , wmem_file_scope ( ) ) ;
 media_packet_times = wmem_tree_new_autoreset ( wmem_epan_scope ( ) , wmem_file_scope ( ) ) ;

