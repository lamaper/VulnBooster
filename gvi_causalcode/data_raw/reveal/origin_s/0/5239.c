void proto_register_q931 ( void ) {
 guint i ;
 guint last_offset ;
 static hf_register_info hf [ ] = {
 {
 & hf_q931_discriminator , {
 "Protocol discriminator" , "q931.disc" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_call_ref_len , {
 "Call reference value length" , "q931.call_ref_len" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_call_ref_flag , {
 "Call reference flag" , "q931.call_ref_flag" , FT_BOOLEAN , BASE_NONE , TFS ( & tfs_call_ref_flag ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_call_ref , {
 "Call reference value" , "q931.call_ref" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_message_type , {
 "Message type" , "q931.message_type" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_message_type_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_maintenance_message_type , {
 "Maintenance message type" , "q931.maintenance_message_type" , FT_UINT8 , BASE_HEX , VALS ( dms_message_type_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_segment_type , {
 "Segmented message type" , "q931.segment_type" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_message_type_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_coding_standard , {
 "Coding standard" , "q931.coding_standard" , FT_UINT8 , BASE_HEX , VALS ( q931_coding_standard_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_q931_interpretation , {
 "Interpretation" , "q931.interpretation" , FT_UINT8 , BASE_HEX , VALS ( q931_interpretation_vals ) , 0x1C , NULL , HFILL }
 }
 , {
 & hf_q931_pres_meth_prot_prof , {
 "Presentation method of protocol profile" , "q931.presentation_method_protocol_profile" , FT_UINT8 , BASE_HEX , VALS ( q931_pres_meth_prot_prof_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_q931_high_layer_characteristics , {
 "High layer characteristics identification" , "q931.high_layer_characteristics" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_high_layer_characteristics_vals_ext , 0x7f , NULL , HFILL }
 }
 , {
 & hf_q931_extended_high_layer_characteristics , {
 "Extended high layer characteristics identification" , "q931.extended_high_layer_characteristics" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_extended_high_layer_characteristics_vals_ext , 0x7f , NULL , HFILL }
 }
 , {
 & hf_q931_extended_audiovisual_characteristics , {
 "Extended audiovisual characteristics identification" , "q931.extended_audiovisual_characteristics" , FT_UINT8 , BASE_HEX , VALS ( q931_audiovisual_characteristics_vals ) , 0x7f , NULL , HFILL }
 }
 , {
 & hf_q931_information_transfer_capability , {
 "Information transfer capability" , "q931.information_transfer_capability" , FT_UINT8 , BASE_HEX , VALS ( q931_information_transfer_capability_vals ) , 0x1f , NULL , HFILL }
 }
 , {
 & hf_q931_transfer_mode , {
 "Transfer mode" , "q931.transfer_mode" , FT_UINT8 , BASE_HEX , VALS ( q931_transfer_mode_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_q931_information_transfer_rate , {
 "Information transfer rate" , "q931.information_transfer_rate" , FT_UINT8 , BASE_HEX , VALS ( q931_information_transfer_rate_vals ) , 0x1f , NULL , HFILL }
 }
 , {
 & hf_q931_layer_ident , {
 "Layer identification" , "q931.layer_ident" , FT_UINT8 , BASE_HEX , VALS ( q931_bearer_capability_layer_ident_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_q931_uil1 , {
 "User information layer 1 protocol" , "q931.uil1" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_uil1_vals_ext , 0x1f , NULL , HFILL }
 }
 , {
 & hf_q931_cause_location , {
 "Cause location" , "q931.cause_location" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & q931_cause_location_vals_ext , 0x0f , NULL , HFILL }
 }
 , {
 & hf_q931_cause_value , {
 "Cause value" , "q931.cause_value" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & q931_cause_code_vals_ext , 0x7f , NULL , HFILL }
 }
 , {
 & hf_q931_number_type , {
 "Number type" , "q931.number_type" , FT_UINT8 , BASE_HEX , VALS ( q931_number_type_vals ) , 0x70 , NULL , HFILL }
 }
 , {
 & hf_q931_numbering_plan , {
 "Numbering plan" , "q931.numbering_plan" , FT_UINT8 , BASE_HEX , VALS ( q931_numbering_plan_vals ) , 0x0f , NULL , HFILL }
 }
 , {
 & hf_q931_screening_ind , {
 "Screening indicator" , "q931.screening_ind" , FT_UINT8 , BASE_HEX , VALS ( q931_screening_indicator_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_q931_presentation_ind , {
 "Presentation indicator" , "q931.presentation_ind" , FT_UINT8 , BASE_HEX , VALS ( q931_presentation_indicator_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_q931_extension_ind , {
 "Extension indicator" , "q931.extension_ind" , FT_BOOLEAN , 8 , TFS ( & q931_extension_ind_value ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_q931_extension_ind_preference , {
 "Preference" , "q931.extension_ind_preference" , FT_UINT8 , BASE_DEC , VALS ( q931_status_preference_vals ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_q931_extension_ind_new_status , {
 "New status" , "q931.extension_ind_new_status" , FT_UINT8 , BASE_DEC , VALS ( q931_new_status_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_q931_calling_party_number , {
 "Calling party number digits" , "q931.calling_party_number.digits" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_called_party_number , {
 "Called party number digits" , "q931.called_party_number.digits" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_connected_number , {
 "Connected party number digits" , "q931.connected_number.digits" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_redirecting_number , {
 "Redirecting party number digits" , "q931.redirecting_number.digits" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_channel_interface_explicit , {
 "Interface identifier present" , "q931.channel.interface_id_present" , FT_BOOLEAN , 8 , NULL , 0x40 , "True if the interface identifier is explicit in the following octets" , HFILL }
 }
 , {
 & hf_q931_channel_interface_type , {
 "Interface type" , "q931.channel.interface_type" , FT_BOOLEAN , 8 , TFS ( & tfs_interface_type ) , 0x20 , "Identifies the ISDN interface type" , HFILL }
 }
 , {
 & hf_q931_channel_exclusive , {
 "Indicated channel" , "q931.channel.exclusive" , FT_BOOLEAN , 8 , TFS ( & tfs_channel_exclusive ) , 0x08 , "True if only the indicated channel is acceptable" , HFILL }
 }
 , {
 & hf_q931_channel_dchan , {
 "D-channel indicator" , "q931.channel.dchan" , FT_BOOLEAN , 8 , NULL , 0x04 , "True if the identified channel is the D-Channel" , HFILL }
 }
 , {
 & hf_q931_channel_selection_bri , {
 "Information channel selection" , "q931.channel.selection" , FT_UINT8 , BASE_HEX , VALS ( q931_basic_channel_selection_vals ) , 0x03 , "Identifies the information channel to be used" , HFILL }
 }
 , {
 & hf_q931_channel_selection_pri , {
 "Information channel selection" , "q931.channel.selection" , FT_UINT8 , BASE_HEX , VALS ( q931_not_basic_channel_selection_vals ) , 0x03 , "Identifies the information channel to be used" , HFILL }
 }
 , {
 & hf_q931_channel_map , {
 "Number/map" , "q931.channel.map" , FT_BOOLEAN , 8 , TFS ( & tfs_channel_map ) , 0x10 , "True if channel is indicates by channel map rather than number" , HFILL }
 }
 , {
 & hf_q931_channel_element_type , {
 "Element type" , "q931.channel.element_type" , FT_UINT8 , BASE_HEX , VALS ( q931_element_type_vals ) , 0xF , "Type of element in the channel number/slot map octets" , HFILL }
 }
 , {
 & hf_q931_channel_number , {
 "Channel number" , "q931.channel.number" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_segment_overlap , {
 "Segment overlap" , "q931.segment.overlap" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , "Fragment overlaps with other fragments" , HFILL }
 }
 , {
 & hf_q931_segment_overlap_conflict , {
 "Conflicting data in fragment overlap" , "q931.segment.overlap.conflict" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , "Overlapping fragments contained conflicting data" , HFILL }
 }
 , {
 & hf_q931_segment_multiple_tails , {
 "Multiple tail fragments found" , "q931.segment.multipletails" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , "Several tails were found when defragmenting the packet" , HFILL }
 }
 , {
 & hf_q931_segment_too_long_segment , {
 "Segment too long" , "q931.segment.toolongfragment" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , "Segment contained data past end of packet" , HFILL }
 }
 , {
 & hf_q931_segment_error , {
 "Defragmentation error" , "q931.segment.error" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , "Defragmentation error due to illegal fragments" , HFILL }
 }
 , {
 & hf_q931_segment_count , {
 "Segment count" , "q931.segment.count" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_segment , {
 "Q.931 Segment" , "q931.segment" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_segments , {
 "Q.931 Segments" , "q931.segments" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_reassembled_in , {
 "Reassembled Q.931 in frame" , "q931.reassembled_in" , FT_FRAMENUM , BASE_NONE , NULL , 0x0 , "This Q.931 message is reassembled in this frame" , HFILL }
 }
 , {
 & hf_q931_reassembled_length , {
 "Reassembled Q.931 length" , "q931.reassembled.length" , FT_UINT32 , BASE_DEC , NULL , 0x0 , "The total length of the reassembled payload" , HFILL }
 }
 , {
 & hf_q931_first_segment , {
 "First segment" , "q931.segment.first" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_not_first_segment , {
 "Not first segment" , "q931.segment.not_first" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_data , {
 "Data" , "q931.bearer_capability.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_rate_multiplier , {
 "Rate multiplier" , "q931.bearer_capability.rate_multiplier" , FT_UINT8 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_user_rate , {
 "User rate" , "q931.bearer_capability.user_rate" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_l1_user_rate_vals_ext , 0x1F , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_intermediate_rate , {
 "Intermediate rate" , "q931.bearer_capability.intermediate_rate" , FT_UINT8 , BASE_HEX , VALS ( q931_l1_intermediate_rate_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_stop_bits , {
 "Stop bits" , "q931.bearer_capability.stop_bits" , FT_UINT8 , BASE_HEX , VALS ( q931_l1_stop_bits_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_data_bits , {
 "Data bits" , "q931.bearer_capability.data_bits" , FT_UINT8 , BASE_HEX , VALS ( q931_l1_data_bits_vals ) , 0x18 , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_parity , {
 "Parity" , "q931.bearer_capability.parity" , FT_UINT8 , BASE_HEX , VALS ( q931_l1_parity_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_modem_type , {
 "Modem type" , "q931.bearer_capability.modem_type" , FT_UINT8 , BASE_HEX | BASE_RANGE_STRING , RVALS ( q931_l1_modem_type_rvals ) , 0x3F , NULL , HFILL }
 }
 , {
 & hf_q931_uil2 , {
 "User information layer 2 protocol" , "q931.uil2" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_uil2_vals_ext , 0x1F , NULL , HFILL }
 }
 , {
 & hf_q931_uil2_info , {
 "User-specified layer 2 protocol information" , "q931.uil2_info" , FT_UINT8 , BASE_HEX , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_mode , {
 "Mode" , "q931.bearer_capability.mode" , FT_UINT8 , BASE_HEX , VALS ( q931_mode_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_window_size , {
 "Window size" , "q931.bearer_capability.window_size" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_uil3 , {
 "User information layer 3 protocol" , "q931.uil3" , FT_UINT8 , BASE_HEX , VALS ( q931_uil3_vals ) , 0x1F , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_default_packet_size , {
 "Default packet size" , "q931.bearer_capability.default_packet_size" , FT_UINT8 , BASE_DEC , NULL , 0x0F , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_packet_window_size , {
 "Packet window size" , "q931.bearer_capability.packet_window_size" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_uil3_additional , {
 "Additional layer 3 protocol information" , "q931.uil3_additional" , FT_UINT16 , BASE_HEX , VALS ( nlpid_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_cause_data , {
 "Data" , "q931.cause.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_cause_recommendation , {
 "Recommendation" , "q931.cause.recommendation" , FT_UINT8 , BASE_HEX , VALS ( q931_cause_recommendation_vals ) , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_cause_call_rejection_reason , {
 "Rejection reason" , "q931.cause_call.rejection_reason" , FT_UINT8 , BASE_HEX , VALS ( q931_rejection_reason_vals ) , 0x7C , NULL , HFILL }
 }
 , {
 & hf_q931_cause_call_condition , {
 "Condition" , "q931.cause_call.condition" , FT_UINT8 , BASE_HEX , VALS ( q931_cause_condition_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_q931_cause_call_user_specific_diagnostic , {
 "User specific diagnostic" , "q931.cause_call.user_specific_diagnostic" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_cause_call_diagnostic , {
 "Diagnostic" , "q931.cause_call.diagnostic" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_cause_call_message_type , {
 "Message type" , "q931.cause_call.message_type" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_message_type_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_cause_call_rec_timer , {
 "Timer" , "q931.cause_call.rec_timer" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_call_state_data , {
 "Data" , "q931.call_state.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_call_state , {
 "Call state" , "q931.call_state" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_call_state_vals_ext , 0x3F , NULL , HFILL }
 }
 , {
 & hf_q931_channel_interface_id , {
 "Interface ID" , "q931.channel.interface_id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_channel_data , {
 "Data" , "q931.channel.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_channel_slot_map , {
 "Slot map" , "q931.channel.slot_map" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_progress_indicator_data , {
 "Data" , "q931.progress_indicator.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_progress_indicator_location , {
 "Location" , "q931.progress_indicator.location" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_cause_location_vals_ext , 0x0F , NULL , HFILL }
 }
 , {
 & hf_q931_progress_indicator_description , {
 "Progress description" , "q931.progress_indicator.description" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_progress_description_vals_ext , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_netid_length , {
 "Network identification length" , "q931.netid.length" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_netid_type , {
 "Type of network identification" , "q931.netid.type" , FT_UINT8 , BASE_HEX , VALS ( q931_netid_type_vals ) , 0x70 , NULL , HFILL }
 }
 , {
 & hf_q931_netid_plan , {
 "Network identification plan" , "q931.netid.plan" , FT_UINT8 , BASE_HEX , VALS ( q931_netid_plan_vals ) , 0x0F , NULL , HFILL }
 }
 , {
 & hf_q931_netid , {
 "Network identification" , "q931.netid" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_netid_facility_specification , {
 "Network-specific facility specification" , "q931.netid.facility_specification" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_notification_description , {
 "Notification description" , "q931.notification_description" , FT_UINT8 , BASE_HEX , VALS ( q931_notification_description_vals ) , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_signal , {
 "Signal" , "q931.signal" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_signal_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_information_rate_incoming , {
 "Incoming information rate" , "q931.information_rate.incoming" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_throughput_class_vals_ext , 0x1F , NULL , HFILL }
 }
 , {
 & hf_q931_information_rate_outgoing , {
 "Outgoing information rate" , "q931.information_rate.outgoing" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_throughput_class_vals_ext , 0x1F , NULL , HFILL }
 }
 , {
 & hf_q931_information_rate_minimum_incoming , {
 "Minimum incoming information rate" , "q931.information_rate.minimum_incoming" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_throughput_class_vals_ext , 0x1F , NULL , HFILL }
 }
 , {
 & hf_q931_information_rate_minimum_outgoing , {
 "Minimum outgoing information rate" , "q931.information_rate.minimum_outgoing" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_throughput_class_vals_ext , 0x1F , NULL , HFILL }
 }
 , {
 & hf_q931_fast_select , {
 "Fast select" , "q931.fast_select" , FT_UINT8 , BASE_HEX , VALS ( q931_fast_selected_vals ) , 0x18 , NULL , HFILL }
 }
 , {
 & hf_q931_pl_window_size_forward_value , {
 "Forward value" , "q931.pl_window_size.forward_value" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_pl_window_size_backward_value , {
 "Backward value" , "q931.pl_window_size.backward_value" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_packet_size_forward_value , {
 "Forward value" , "q931.packet_size.forward_value" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_packet_size_backward_value , {
 "Backward value" , "q931.packet_size.backward_value" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_q931_cug_indication , {
 "CUG indication" , "q931.cug_indication" , FT_UINT8 , BASE_HEX , VALS ( q931_cug_indication_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_q931_cug_index_code , {
 "CUG index code" , "q931.cug_index_code" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_reverse_charging_ind , {
 "Reverse charging indication" , "q931.reverse_charging_ind" , FT_UINT8 , BASE_HEX , VALS ( q931_reverse_charging_indication_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_q931_extension_reason , {
 "Reason for redirection" , "q931.extension.reason" , FT_UINT8 , BASE_HEX , VALS ( q931_redirection_reason_vals ) , 0x0F , NULL , HFILL }
 }
 , {
 & hf_q931_party_subaddr_type , {
 "Type of subaddress" , "q931.party_subaddr.type" , FT_UINT8 , BASE_HEX , VALS ( q931_subaddress_type_vals ) , 0x70 , NULL , HFILL }
 }
 , {
 & hf_q931_party_subaddr_odd_even_indicator , {
 "Odd/even indicator" , "q931.party_subaddr.odd_even" , FT_UINT8 , BASE_HEX , VALS ( q931_odd_even_indicator_vals ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_q931_party_subaddr , {
 "Subaddress" , "q931.party_subaddr" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_restart_indicator , {
 "Restart indicator" , "q931.restart_indicator" , FT_UINT8 , BASE_HEX , VALS ( q931_restart_indicator_class_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_q931_high_layer_compat_data , {
 "Data" , "q931.high_layer_compat.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_user_protocol_discriminator , {
 "Protocol discriminator" , "q931.user.protocol_discriminator" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & q931_protocol_discriminator_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_user_information_len , {
 "User information" , "q931.user.len" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_user_information_str , {
 "User information" , "q931.user.string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_user_information_bytes , {
 "User information" , "q931.user.bytes" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_party_category , {
 "Party category" , "q931.party_category" , FT_UINT8 , BASE_HEX , VALS ( q931_party_category_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_q931_congestion_level , {
 "Congestion level" , "q931.congestion_level" , FT_UINT8 , BASE_HEX , VALS ( q931_congestion_level_vals ) , Q931_IE_SO_IE_MASK , NULL , HFILL }
 }
 , {
 & hf_q931_repeat_indicator , {
 "Repeat indicator" , "q931.repeat_indicator" , FT_UINT8 , BASE_HEX , VALS ( q931_repeat_indication_vals ) , Q931_IE_SO_IE_MASK , NULL , HFILL }
 }
 , {
 & hf_q931_out_band_negotiation , {
 "Out-band negotiation" , "q931.out_band_negotiation" , FT_BOOLEAN , 8 , TFS ( & tfs_possible_not_possible ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_q931_layer_1 , {
 "Layer 1" , "q931.layer_1" , FT_BOOLEAN , 8 , TFS ( & tfs_asynchronous_synchronous ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_q931_layer_1_in_band_negotiation , {
 "Layer 1 in-band negotiation" , "q931.layer_1_in_band_negotiation" , FT_BOOLEAN , 8 , TFS ( & tfs_possible_not_possible ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_q931_send_data_net_independent_clock , {
 "Send data with network independent clock" , "q931.send_data_net_independent_clock" , FT_BOOLEAN , 8 , TFS ( & tfs_required_not_required ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_q931_accept_data_net_independent_clock , {
 "Accept data with network independent clock" , "q931.accept_data_net_independent_clock" , FT_BOOLEAN , 8 , TFS ( & tfs_accepted_not_accepted ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_q931_send_data_flow_control , {
 "Send data with flow control mechanism" , "q931.send_data_flow_control" , FT_BOOLEAN , 8 , TFS ( & tfs_required_not_required ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_q931_accept_data_flow_control , {
 "Accept data with flow control mechanism" , "q931.accept_data_flow_control" , FT_BOOLEAN , 8 , TFS ( & tfs_accepted_not_accepted ) , 0x2 , NULL , HFILL }
 }
 , {
 & hf_q931_rate_adaption_header , {
 "Rate adaption header" , "q931.rate_adaption_header" , FT_BOOLEAN , 8 , TFS ( & tfs_present_not_present ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_q931_multiple_frame_establishment , {
 "Multiple frame establishment" , "q931.multiple_frame_establishment" , FT_BOOLEAN , 8 , TFS ( & tfs_supported_not_supported ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_q931_mode_of_operation , {
 "mode of operation" , "q931.mode_of_operation" , FT_BOOLEAN , 8 , TFS ( & tfs_protocol_sensative_bit_transparent ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_q931_message_originator , {
 "Message originator" , "q931.message_originator" , FT_BOOLEAN , 8 , TFS ( & tfs_assignor_default ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_q931_negotiation_is_done , {
 "Negotiation is done" , "q931.negotiation_is_done" , FT_BOOLEAN , 8 , TFS ( & tfs_in_out_band ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_q931_bearer_capability_duplex , {
 "Duplex" , "q931.bearer_capability.duplex" , FT_BOOLEAN , 8 , TFS ( & tfs_full_half ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_q931_network_service , {
 "Network service" , "q931.network_service" , FT_BOOLEAN , 8 , TFS ( & tfs_user_provider ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_q931_extension_condition_type , {
 "Type" , "q931.extension_condition_type" , FT_BOOLEAN , 8 , TFS ( & tfs_abnormal_normal ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_q931_extension_condition , {
 "Condition" , "q931.extension_condition" , FT_UINT8 , BASE_HEX , VALS ( q931_cause_condition_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_q931_pl_request , {
 "Request" , "q931.pl_request" , FT_BOOLEAN , 8 , TFS ( & tfs_pl_request ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_q931_pl_binary_confirmation , {
 "Confirmation" , "q931.pl_binary_confirmation" , FT_BOOLEAN , 8 , TFS ( & tfs_link_end ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_q931_pl_modulus , {
 "Modulus" , "q931.pl_modulus" , FT_BOOLEAN , 8 , TFS ( & tfs_pl_modulus ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_q931_data , {
 "Data" , "q931.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_information_element , {
 "Information element" , "q931.information_element" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_information_element_len , {
 "Length" , "q931.information_element_len" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_date_time , {
 "Date/time" , "q931.date_time" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_more_data , {
 "More data" , "q931.more_data" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_sending_complete , {
 "Sending complete" , "q931.sending_complete" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_message_segment , {
 "Message segment" , "q931.message_segment" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_missing_info_element , {
 "Missing information element" , "q931.missing_info_element" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_insufficient_info_element , {
 "Insufficient information element" , "q931.insufficient_info_element" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_cumulative_transit_delay , {
 "Cumulative transit delay" , "q931.cumulative_transit_delay" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_requested_end_to_end_transit_delay , {
 "Requested end-to-end transit delay" , "q931.requested_end_to_end_transit_delay" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_maximum_end_to_end_transit_delay , {
 "Maximum end-to-end transit delay" , "q931.maximum_end_to_end_transit_delay" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_transit_delay , {
 "Transit delay" , "q931.transit_delay" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_display_information , {
 "Display information" , "q931.display_information" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_keypad_facility , {
 "Keypad facility" , "q931.keypad_facility" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_avaya_display , {
 "Avaya Display" , "q931.avaya_display" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_locking_codeset , {
 "Locking codeset" , "q931.locking_codeset" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_q931_protocol_negotiation , {
 "Protocol negotiation" , "q931.protocol_negotiation" , FT_BOOLEAN , 8 , TFS ( & tfs_protocol_negotiation ) , 0x08 , NULL , HFILL }
 }
 , }
 ;

 static ei_register_info ei [ ] = {
 {
 & ei_q931_invalid_length , {
 "q931.invalid_length" , PI_MALFORMED , PI_ERROR , "Invalid length" , EXPFILL }
 }
 , {
 & ei_q931_date_time , {
 "q931.date_time.invalid" , PI_MALFORMED , PI_ERROR , "Date/time: Invalid length" , EXPFILL }
 }
 , {
 & ei_q931_information_element , {
 "q931.information_element.unknown" , PI_PROTOCOL , PI_WARN , "Unknown information element" , EXPFILL }
 }
 , {
 & ei_q931_incomplete_ie , {
 "q931.incomplete_ie" , PI_MALFORMED , PI_ERROR , "Incomplete IE in the 1st segment" , EXPFILL }
 }
 , }
 ;
 module_t * q931_module ;
 expert_module_t * expert_q931 ;
 ett [ 0 ] = & ett_q931 ;
 ett [ 1 ] = & ett_q931_segments ;
 ett [ 2 ] = & ett_q931_segment ;
 last_offset = NUM_INDIVIDUAL_ELEMS ;
 for ( i = 0 ;
 i < NUM_IE ;
 i ++ , last_offset ++ ) {
 ett_q931_ie [ i ] = - 1 ;
 ett [ last_offset ] = & ett_q931_ie [ i ] ;
 }
 proto_q931 = proto_register_protocol ( "Q.931" , "Q.931" , "q931" ) ;
 proto_register_field_array ( proto_q931 , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_q931 = expert_register_protocol ( proto_q931 ) ;
 expert_register_field_array ( expert_q931 , ei , array_length ( ei ) ) ;
 register_init_routine ( q931_init ) ;
 register_cleanup_routine ( q931_cleanup ) ;
 q931_handle = register_dissector ( "q931" , dissect_q931 , proto_q931 ) ;
 q931_tpkt_handle = register_dissector ( "q931.tpkt" , dissect_q931_tpkt , proto_q931 ) ;
 q931_tpkt_pdu_handle = create_dissector_handle ( dissect_q931_tpkt_pdu , proto_q931 ) ;
 q931_over_ip_handle = register_dissector ( "q931.over_ip" , dissect_q931_over_ip , proto_q931 ) ;
 register_dissector ( "q931.ie" , dissect_q931_ie_cs0 , proto_q931 ) ;
 register_dissector ( "q931.ie.cs7" , dissect_q931_ie_cs7 , proto_q931 ) ;
 codeset_dissector_table = register_dissector_table ( "q931.codeset" , "Q.931 Codeset" , proto_q931 , FT_UINT8 , BASE_HEX ) ;
 ie_dissector_table = register_dissector_table ( "q931.ie" , "Q.931 IE" , proto_q931 , FT_UINT16 , BASE_HEX ) ;
 q931_user_heur_subdissector_list = register_heur_dissector_list ( "q931_user" , proto_q931 ) ;
 q931_module = prefs_register_protocol ( proto_q931 , NULL ) ;
 prefs_register_bool_preference ( q931_module , "desegment_h323_messages" , "Reassemble Q.931 messages spanning multiple TCP segments" , "Whether the Q.931 dissector should reassemble messages spanning multiple TCP segments." " To use this option, you must also enable \"Allow subdissectors to reassemble TCP streams\" in the TCP protocol settings." , & q931_desegment ) ;
 prefs_register_bool_preference ( q931_module , "reassembly" , "Reassemble segmented Q.931 messages" , "Reassemble segmented Q.931 messages (Q.931 - Annex H)" , & q931_reassembly ) ;
 prefs_register_bool_preference ( q931_module , "iso_iec_cause_coding" , "Decode ISO/IEC cause coding standard as ITU-T" , "Decode ISO/IEC cause coding standard as ITU-T" , & g931_iso_iec_cause ) ;
 q931_tap = register_tap ( "q931" ) ;
 }