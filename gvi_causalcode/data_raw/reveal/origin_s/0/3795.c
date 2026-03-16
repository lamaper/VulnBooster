void proto_register_gsm_a_dtap ( void ) {
 guint i ;
 guint last_offset ;
 static hf_register_info hf [ ] = {
 {
 & hf_gsm_a_seq_no , {
 "Sequence number" , "gsm_a.dtap.seq_no" , FT_UINT8 , BASE_DEC , NULL , 0xc0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_msg_gcc_type , {
 "DTAP Group Call Control Message Type" , "gsm_a.dtap.msg_gcc_type" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_msg_gcc_strings ) , 0x3f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_msg_bcc_type , {
 "DTAP Broadcast Call Control Message Type" , "gsm_a.dtap.msg_bcc_type" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_msg_bcc_strings ) , 0x3f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_msg_mm_type , {
 "DTAP Mobility Management Message Type" , "gsm_a.dtap.msg_mm_type" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_msg_mm_strings ) , 0x3f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_msg_cc_type , {
 "DTAP Call Control Message Type" , "gsm_a.dtap.msg_cc_type" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_msg_cc_strings ) , 0x3f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_msg_sms_type , {
 "DTAP Short Message Service Message Type" , "gsm_a.dtap.msg_sms_type" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_msg_sms_strings ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_msg_ss_type , {
 "DTAP Non call Supplementary Service Message Type" , "gsm_a.dtap.msg_ss_type" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_msg_ss_strings ) , 0x3f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_msg_tp_type , {
 "DTAP Tests Procedures Message Type" , "gsm_a.dtap.msg_tp_type" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_msg_tp_strings ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_elem_id , {
 "Element ID" , "gsm_a.dtap.elem_id" , FT_UINT8 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_cld_party_bcd_num , {
 "Called Party BCD Number" , "gsm_a.dtap.cld_party_bcd_num" , FT_STRING , BASE_NONE , 0 , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_clg_party_bcd_num , {
 "Calling Party BCD Number" , "gsm_a.dtap.clg_party_bcd_num" , FT_STRING , BASE_NONE , 0 , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_conn_num , {
 "Connected Number" , "gsm_a.dtap.conn_num" , FT_STRING , BASE_NONE , 0 , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_red_party_bcd_num , {
 "Redirecting Party BCD Number" , "gsm_a.dtap.red_party_bcd_num" , FT_STRING , BASE_NONE , 0 , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_cause , {
 "DTAP Cause" , "gsm_a.dtap.cause" , FT_UINT8 , BASE_HEX , 0 , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_type_of_number , {
 "Type of number" , "gsm_a.dtap.type_of_number" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_type_of_number_values ) , 0x70 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_numbering_plan_id , {
 "Numbering plan identification" , "gsm_a.dtap.numbering_plan_id" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_numbering_plan_id_values ) , 0x0f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_present_ind , {
 "Presentation indicator" , "gsm_a.dtap.present_ind" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_present_ind_values ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_screening_ind , {
 "Screening indicator" , "gsm_a.dtap.screening_ind" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_screening_ind_values ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_type_of_sub_addr , {
 "Type of subaddress" , "gsm_a.dtap.type_of_sub_addr" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_type_of_sub_addr_values ) , 0x70 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_odd_even_ind , {
 "Odd/even indicator" , "gsm_a.dtap.odd_even_ind" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_odd_even_ind_values ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_lsa_id , {
 "LSA Identifier" , "gsm_a.dtap.lsa_id" , FT_UINT24 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_speech_vers_ind , {
 "Speech version indication" , "gsm_a.dtap.speech_vers_ind" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_speech_vers_ind_values ) , 0x0f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_itc , {
 "Information transfer capability" , "gsm_a.dtap.itc" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_itc_values ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_sysid , {
 "System Identification (SysID)" , "gsm_a.dtap.sysid" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_sysid_values ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bitmap_length , {
 "Bitmap Length" , "gsm_a.dtap.bitmap_length" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_serv_cat_b7 , {
 "Automatically initiated eCall" , "gsm_a.dtap.serv_cat_b7" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_serv_cat_b6 , {
 "Manually initiated eCall" , "gsm_a.dtap.serv_cat_b6" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_serv_cat_b5 , {
 "Mountain Rescue" , "gsm_a.dtap.serv_cat_b5" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_serv_cat_b4 , {
 "Marine Guard" , "gsm_a.dtap.serv_cat_b4" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_serv_cat_b3 , {
 "Fire Brigade" , "gsm_a.dtap.serv_cat_b3" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_serv_cat_b2 , {
 "Ambulance" , "gsm_a.dtap.serv_cat_b2" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_serv_cat_b1 , {
 "Police" , "gsm_a.dtap.serv_cat_b1" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_csmo , {
 "CSMO" , "gsm_a.dtap.csmo" , FT_BOOLEAN , BASE_NONE , TFS ( & gsm_a_dtap_csmo_value ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_csmt , {
 "CSMT" , "gsm_a.dtap.csmt" , FT_BOOLEAN , BASE_NONE , TFS ( & gsm_a_dtap_csmt_value ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_mm_timer_unit , {
 "Unit" , "gsm_a.dtap.mm_timer_unit" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_mm_timer_unit_vals ) , 0xe0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_mm_timer_value , {
 "Timer value" , "gsm_a.dtap.mm_timer_value" , FT_UINT8 , BASE_DEC , NULL , 0x1f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_alerting_pattern , {
 "Alerting Pattern" , "gsm_a.dtap.alerting_pattern" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_alerting_pattern_vals ) , 0x0f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_ccbs_activation , {
 "CCBS Activation" , "gsm_a.dtap.ccbs_activation" , FT_BOOLEAN , 8 , TFS ( & gsm_a_ccbs_activation_value ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_stream_identifier , {
 "Stream Identifier" , "gsm_a.dtap.stream_identifier" , FT_UINT8 , BASE_HEX , 0 , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_mcs , {
 "MCS" , "gsm_a.dtap.mcs" , FT_BOOLEAN , 8 , TFS ( & gsm_a_mcs_value ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_cause_of_no_cli , {
 "Cause of no CLI" , "gsm_a.dtap.cause_of_no_cli" , FT_UINT8 , BASE_HEX , 0 , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_cause_ss_diagnostics , {
 "Supplementary Services Diagnostics" , "gsm_a.dtap.cause_ss_diagnostics" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_cause_ss_diagnostics_vals ) , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_tdma_efr , {
 "TDMA EFR" , "gsm_a.dtap.codec.tdma_efr" , FT_BOOLEAN , 8 , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_umts_amr_2 , {
 "UMTS AMR 2" , "gsm_a.dtap.codec.umts_amr_2" , FT_BOOLEAN , 8 , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_umts_amr , {
 "UMTS AMR" , "gsm_a.dtap.codec.umts_amr" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_hr_amr , {
 "HR AMR" , "gsm_a.dtap.codec.hr_amr" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_fr_amr , {
 "FR AMR" , "gsm_a.dtap.codec.fr_amr" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_gsm_efr , {
 "GSM EFR" , "gsm_a.dtap.codec.gsm_efr" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_gsm_hr , {
 "GSM HR" , "gsm_a.dtap.codec.gsm_hr" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_gsm_fr , {
 "GSM FR" , "gsm_a.dtap.codec.gsm_fr" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_ohr_amr_wb , {
 "OHR AMR-WB" , "gsm_a.dtap.codec.ohr_amr_wb" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_ofr_amr_wb , {
 "OFR AMR-WB" , "gsm_a.dtap.codec.ofr_amr_wb" , FT_BOOLEAN , 8 , NULL , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_ohr_amr , {
 "OHR AMR" , "gsm_a.dtap.codec.ohr_amr" , FT_BOOLEAN , 8 , NULL , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_umts_amr_wb , {
 "UMTS AMR-WB" , "gsm_a.dtap.codec.umts_amr_wb" , FT_BOOLEAN , 8 , NULL , 0x04 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_fr_amr_wb , {
 "FR AMR-WB" , "gsm_a.dtap.codec.fr_amr_wb" , FT_BOOLEAN , 8 , NULL , 0x02 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_codec_pdc_efr , {
 "PDC EFR" , "gsm_a.dtap.codec.pdc_efr" , FT_BOOLEAN , 8 , NULL , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_notification_description , {
 "Notification description" , "gsm_a.dtap.notif_descr" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_notification_description_vals ) , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_emerg_num_info_length , {
 "Emergency Number Info length" , "gsm_a.dtap.emerg_num_info_length" , FT_UINT8 , BASE_DEC , 0 , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_emergency_bcd_num , {
 "Emergency BCD Number" , "gsm_a.dtap.emergency_bcd_num" , FT_STRING , BASE_NONE , 0 , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_signal_value , {
 "Signal value" , "gsm_a.dtap.signal_value" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_signal_value_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_recall_type , {
 "Recall type" , "gsm_a.dtap.recall_type" , FT_UINT8 , BASE_HEX | BASE_RANGE_STRING , RVALS ( gsm_a_dtap_recall_type_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_coding_standard , {
 "Coding standard" , "gsm_a.dtap.coding_standard" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_coding_standard_vals ) , 0xc0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_call_state , {
 "Call state" , "gsm_a.dtap.call_state" , FT_UINT8 , BASE_DEC , NULL , 0x3f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_prog_coding_standard , {
 "Coding standard" , "gsm_a.dtap.coding_standard" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_coding_standard_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_location , {
 "Location" , "gsm_a.dtap.location" , FT_UINT8 , BASE_HEX , VALS ( gsm_a_dtap_location_vals ) , 0x0f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_progress_description , {
 "Progress description" , "gsm_a.dtap.progress_description" , FT_UINT8 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_afi , {
 "Authority and Format Identifier" , "gsm_a.dtap.afi" , FT_UINT8 , BASE_HEX | BASE_EXT_STRING , & x213_afi_value_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_rej_cause , {
 "Reject cause" , "gsm_a.dtap.rej_cause" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_timezone , {
 "Timezone" , "gsm_a.dtap.timezone" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_u2u_prot_discr , {
 "User-user protocol discriminator" , "gsm_a.dtap.u2u_prot_discr" , FT_UINT8 , BASE_HEX | BASE_RANGE_STRING , RVALS ( gsm_a_dtap_u2u_prot_discr_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_mcat , {
 "MCAT" , "gsm_a.dtap.mcat" , FT_BOOLEAN , 8 , TFS ( & gsm_a_dtap_mcat_value ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_enicm , {
 "ENICM" , "gsm_a.dtap.mcat" , FT_BOOLEAN , 8 , TFS ( & gsm_a_dtap_enicm_value ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_rand , {
 "RAND value" , "gsm_a.dtap.rand" , FT_BYTES , FT_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_autn , {
 "AUTN value" , "gsm_a.dtap.autn" , FT_BYTES , FT_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_sres , {
 "SRES value" , "gsm_a.dtap.sres" , FT_BYTES , FT_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_xres , {
 "XRES value" , "gsm_a.dtap.xres" , FT_BYTES , FT_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_auts , {
 "AUTS value" , "gsm_a.dtap.auts" , FT_BYTES , FT_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_autn_sqn_xor_ak , {
 "SQN xor AK" , "gsm_a.dtap.autn.sqn_xor_ak" , FT_BYTES , FT_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_autn_amf , {
 "AMF" , "gsm_a.dtap.autn.amf" , FT_BYTES , FT_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_autn_mac , {
 "MAC" , "gsm_a.dtap.autn.mac" , FT_BYTES , FT_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_auts_sqn_ms_xor_ak , {
 "SQN_MS xor AK" , "gsm_a.dtap.auts.sqn_ms_xor_ak" , FT_BYTES , FT_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_auts_mac_s , {
 "MAC-S" , "gsm_a.dtap.auts.mac_s" , FT_BYTES , FT_NONE , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_ue_tl_mode , {
 "UE test loop mode" , "gsm_a.dtap.epc.ue_tl_mode" , FT_UINT8 , BASE_DEC , VALS ( epc_ue_test_loop_mode_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_ue_tl_a_ul_sdu_size , {
 "Uplink PDCP SDU size in bits" , "gsm_a.dtap.epc.ue_tl_a_ul_sdu_size" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_ue_tl_a_drb , {
 "Data Radio Bearer identity number" , "gsm_a.dtap.epc.ue_tl_a_drb" , FT_UINT8 , BASE_DEC , NULL , 0x1f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_ue_tl_b_ip_pdu_delay , {
 "IP PDU delay in seconds" , "gsm_a.dtap.epc.ue_tl_b_ip_pdu_delay" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_ue_tl_c_mbsfn_area_id , {
 "MBSFN area identity" , "gsm_a.dtap.epc.ue_tl_c_mbsfn_area_id" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_ue_tl_c_mch_id , {
 "MCH identity" , "gsm_a.dtap.epc.ue_tl_c_mch_id" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_ue_tl_c_lcid , {
 "Logical channel identity" , "gsm_a.dtap.epc.ue_tl_c_lcid" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_ue_positioning_technology , {
 "UE positioning technology" , "gsm_a.dtap.epc.ue_positioning_technology" , FT_UINT8 , BASE_DEC , VALS ( epc_ue_positioning_technology_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_mbms_packet_counter_value , {
 "MBMS packet counter value" , "gsm_a.dtap.epc.mbms_packet_counter_value" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_latitude_sign , {
 "Latitude Sign" , "gsm_a.dtap.epc.latitude_sign" , FT_BOOLEAN , BASE_NONE , TFS ( & epc_latitude_sign_value ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_degrees_latitude , {
 "Degrees Latitude" , "gsm_a.dtap.epc.degrees_latitude" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_degrees_longitude , {
 "Degrees Longitude" , "gsm_a.dtap.epc.degrees_longitude" , FT_INT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_altitude_dir , {
 "Altitude Direction" , "gsm_a.dtap.epc.altitude_direction" , FT_BOOLEAN , BASE_NONE , TFS ( & epc_altitude_dir_value ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_altitude , {
 "Altitude" , "gsm_a.dtap.epc.altitude" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_bearing , {
 "Bearing" , "gsm_a.dtap.epc.bearing" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_horizontal_speed , {
 "Horizontal Speed" , "gsm_a.dtap.epc.horizontal_speed" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_epc_gnss_tod_msec , {
 "GNSS-TOD-msec" , "gsm_a.dtap.epc.gnss_tod_msec" , FT_UINT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_call_ref , {
 "Call Reference" , "gsm_a.dtap.gcc.call_ref" , FT_UINT32 , BASE_DEC , NULL , 0xffffffe0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_call_ref_has_priority , {
 "Call Reference includes priority" , "gsm_a.dtap.gcc.call_ref_has_priority" , FT_BOOLEAN , 32 , NULL , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_call_priority , {
 "Call Priority" , "gsm_a.dtap.gcc.call_priority" , FT_UINT32 , BASE_DEC , VALS ( gcc_call_ref_priority ) , 0x0000000e , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_call_state , {
 "Call state" , "gsm_a.dtap.gcc.call_state" , FT_UINT24 , BASE_DEC , VALS ( gcc_call_state_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_cause_structure , {
 "Cause structure" , "gsm_a.dtap.gcc.cause_structure" , FT_BOOLEAN , 8 , TFS ( & gcc_cause_structure_val ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_cause , {
 "Cause" , "gsm_a.dtap.gcc.cause" , FT_UINT8 , BASE_DEC | BASE_RANGE_STRING , RVALS ( gcc_cause_vals ) , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_orig_ind , {
 "Originator indication" , "gsm_a.dtap.gcc.orig_ind" , FT_BOOLEAN , 8 , TFS ( & gcc_orig_ind_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_state_attr , {
 "State attributes" , "gsm_a.dtap.gcc.state_attr" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_state_attr_da , {
 "DA" , "gsm_a.dtap.gcc.state_attr_da" , FT_BOOLEAN , 8 , TFS ( & gcc_state_attr_da ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_state_attr_ua , {
 "UA" , "gsm_a.dtap.gcc.state_attr_ua" , FT_BOOLEAN , 8 , TFS ( & gcc_state_attr_ua ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_state_attr_comm , {
 "COMM" , "gsm_a.dtap.gcc.state_attr_comm" , FT_BOOLEAN , 8 , TFS ( & gcc_state_attr_comm ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_state_attr_oi , {
 "OI" , "gsm_a.dtap.gcc.state_attr_oi" , FT_BOOLEAN , 8 , TFS ( & gcc_state_attr_oi ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_spare_1 , {
 "Spare_1 (This field shall be ignored)" , "gsm_a.dtap.gcc.spare_1" , FT_UINT32 , BASE_DEC , NULL , 0x00000001 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_spare_3 , {
 "Spare_3 (This field shall be ignored)" , "gsm_a.dtap.gcc.spare_3" , FT_UINT8 , BASE_DEC , NULL , 0x0e , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_gcc_spare_4 , {
 "Spare_4 (This field shall be ignored)" , "gsm_a.dtap.gcc.spare_4" , FT_UINT32 , BASE_DEC , NULL , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_call_ref , {
 "Call Reference" , "gsm_a.dtap.bcc.call_ref" , FT_UINT32 , BASE_DEC , NULL , 0xffffffe0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_call_ref_has_priority , {
 "Call Reference includes priority" , "gsm_a.dtap.bcc.call_ref_has_priority" , FT_BOOLEAN , 32 , NULL , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_call_priority , {
 "Call Priority" , "gsm_a.dtap.bcc.call_priority" , FT_UINT32 , BASE_DEC , VALS ( bcc_call_ref_priority ) , 0x0000000e , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_call_state , {
 "Call state" , "gsm_a.dtap.bcc.call_state" , FT_UINT24 , BASE_DEC | BASE_RANGE_STRING , RVALS ( bcc_call_state_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_cause_structure , {
 "Cause structure" , "gsm_a.dtap.bcc.cause_structure" , FT_BOOLEAN , 8 , TFS ( & bcc_cause_structure_val ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_cause , {
 "Cause" , "gsm_a.dtap.bcc.cause" , FT_UINT8 , BASE_DEC | BASE_RANGE_STRING , RVALS ( bcc_cause_vals ) , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_orig_ind , {
 "Originator indication" , "gsm_a.dtap.bcc.orig_ind" , FT_BOOLEAN , 8 , TFS ( & bcc_orig_ind_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_state_attr , {
 "State attributes" , "gsm_a.dtap.bcc.state_attr" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_state_attr_da , {
 "DA" , "gsm_a.dtap.bcc.state_attr_da" , FT_BOOLEAN , 8 , TFS ( & bcc_state_attr_da ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_state_attr_ua , {
 "UA" , "gsm_a.dtap.bcc.state_attr_ua" , FT_BOOLEAN , 8 , TFS ( & bcc_state_attr_ua ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_state_attr_comm , {
 "COMM" , "gsm_a.dtap.bcc.state_attr_comm" , FT_BOOLEAN , 8 , TFS ( & bcc_state_attr_comm ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_state_attr_oi , {
 "OI" , "gsm_a.dtap.bcc.state_attr_oi" , FT_BOOLEAN , 8 , TFS ( & bcc_state_attr_oi ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_compr_otdi , {
 "Compressed otdi" , "gsm_a.dtap.bcc.compr_otdi" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_spare_1 , {
 "Spare_1 (This field shall be ignored)" , "gsm_a.dtap.bcc.spare_1" , FT_UINT32 , BASE_DEC , NULL , 0x00000001 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_spare_3 , {
 "Spare_3 (This field shall be ignored)" , "gsm_a.dtap.bcc.spare_3" , FT_UINT8 , BASE_DEC , NULL , 0x0e , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bcc_spare_4 , {
 "Spare_4 (This field shall be ignored)" , "gsm_a.dtap.bcc.spare_4" , FT_UINT32 , BASE_DEC , NULL , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_coding_scheme , {
 "Coding Scheme" , "gsm_a.dtap.coding_scheme" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_coding_scheme_vals ) , 0x70 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_add_ci , {
 "Add CI" , "gsm_a.dtap.add_ci" , FT_BOOLEAN , 8 , TFS ( & tfs_add_ci ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_number_of_spare_bits , {
 "Number of spare bits in last octet" , "gsm_a.dtap.number_of_spare_bits" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_number_of_spare_bits_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_text_string , {
 "Text String" , "gsm_a.dtap.text_string" , FT_STRING , STR_UNICODE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_time_zone_time , {
 "Time" , "gsm_a.dtap.time_zone_time" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_UTC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_dst_adjustment , {
 "DST Adjustment" , "gsm_a.dtap.dst_adjustment" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_dst_adjustment_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_emergency_number_information , {
 "Emergency Number Information" , "gsm_a.dtap.emergency_number_information" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_mm_timer , {
 "MM Timer" , "gsm_a.dtap.mm_timer" , FT_UINT8 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_hold_auxiliary_state , {
 "Hold auxiliary state" , "gsm_a.dtap.hold_auxiliary_state" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_hold_auxilary_state_vals ) , 0x0C , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_multi_party_auxiliary_state , {
 "Multi party auxiliary state" , "gsm_a.dtap.multi_party_auxiliary_state" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_multi_party_auxilary_state_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_radio_channel_requirement , {
 "Radio channel requirement" , "gsm_a.dtap.radio_channel_requirement" , FT_UINT8 , BASE_DEC , NULL , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_bearer_cap_coding_standard , {
 "Coding standard" , "gsm_a.dtap.cap_coding_standard" , FT_BOOLEAN , 8 , TFS ( & tfs_bearer_cap_coding_standard ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_transfer_mode , {
 "Transfer mode" , "gsm_a.dtap.transfer_mode" , FT_BOOLEAN , 8 , TFS ( & tfs_bearer_cap_transfer_mode ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_coding , {
 "Coding" , "gsm_a.dtap.coding" , FT_BOOLEAN , 8 , TFS ( & tfs_bearer_cap_coding ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_compression , {
 "Compression" , "gsm_a.dtap.compression" , FT_BOOLEAN , 8 , TFS ( & tfs_possible_not_possible ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_compression_up , {
 "Compression" , "gsm_a.dtap.compression" , FT_BOOLEAN , 8 , TFS ( & tfs_allowed_not_allowed ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_structure , {
 "Structure" , "gsm_a.dtap.structure" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_structure_vals ) , 0x30 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_duplex_mode , {
 "Duplex mode" , "gsm_a.dtap.duplex_mode" , FT_BOOLEAN , 8 , TFS ( & tfs_full_half ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_subaddress , {
 "Subaddress" , "gsm_a.dtap.subaddress" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_subaddress_information , {
 "Subaddress information" , "gsm_a.dtap.subaddress_information" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_message_elements , {
 "Message Elements" , "gsm_a.dtap.message_elements" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_rpdu , {
 "RPDU" , "gsm_a.dtap.rpdu" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_configuration , {
 "Configuration" , "gsm_a.dtap.configuration" , FT_BOOLEAN , 8 , TFS ( & tfs_bearer_cap_configuration ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_nirr , {
 "NIRR" , "gsm_a.dtap.nirr" , FT_BOOLEAN , 8 , TFS ( & tfs_nirr ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_establishment , {
 "Establishment" , "gsm_a.dtap.establishment" , FT_BOOLEAN , 8 , TFS ( & tfs_bearer_cap_establishment ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_access_identity , {
 "Access Identity" , "gsm_a.dtap.access_identity" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_access_identity_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_rate_adaption , {
 "Rate Adaption" , "gsm_a.dtap.rate_adaption" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_rate_adaption_vals ) , 0x18 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_signalling_access_protocol , {
 "Signalling Access Protocol" , "gsm_a.dtap.signalling_access_protocol" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_signal_access_protocol_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_other_itc , {
 "Other ITC" , "gsm_a.dtap.other_itc" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_other_itc_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_other_rate_adaption , {
 "Other Rate Adaption" , "gsm_a.dtap.other_rate_adaption" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_other_rate_adaption_vals ) , 0x18 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_rate_adaption_header , {
 "Rate Adaption Header" , "gsm_a.dtap.rate_adaption_header" , FT_BOOLEAN , 8 , TFS ( & tfs_included_not_included ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_multiple_frame_establishment_support , {
 "Multiple frame establishment support in data link" , "gsm_a.dtap.multiple_frame_establishment_support" , FT_BOOLEAN , 8 , TFS ( & tfs_frame_est_supported_not_supported ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_mode_of_operation , {
 "Mode of operation" , "gsm_a.dtap.mode_of_operation" , FT_BOOLEAN , 8 , TFS ( & tfs_protocol_sensative_bit_transparent ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_logical_link_identifier_negotiation , {
 "Logical link identifier negotiation" , "gsm_a.dtap.logical_link_identifier_negotiation" , FT_BOOLEAN , 8 , TFS ( & tfs_log_link_neg ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_assignor_assignee , {
 "Assignor/Assignee" , "gsm_a.dtap.assignor_assignee" , FT_BOOLEAN , 8 , TFS ( & tfs_assignor_assignee ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_in_out_band , {
 "In band/Out of band negotiation" , "gsm_a.dtap.in_out_band" , FT_BOOLEAN , 8 , TFS ( & tfs_in_out_band ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_layer_1_identity , {
 "Layer 1 Identity" , "gsm_a.dtap.layer_1_identity" , FT_UINT8 , BASE_DEC , NULL , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_user_information_layer_1_protocol , {
 "User information layer 1 protocol" , "gsm_a.dtap.user_information_layer_1_protocol" , FT_UINT8 , BASE_DEC , NULL , 0x1e , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_synchronous , {
 "Synchronous/asynchronous" , "gsm_a.dtap.synchronous" , FT_BOOLEAN , 8 , TFS ( & tfs_asynchronous_synchronous ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_number_of_stop_bits , {
 "Number of Stop Bits" , "gsm_a.dtap.number_of_stop_bits" , FT_BOOLEAN , 8 , TFS ( & tfs_stop_bits ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_negotiation , {
 "Negotiation" , "gsm_a.dtap.negotiation" , FT_BOOLEAN , 8 , TFS ( & tfs_negotiation ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_number_of_data_bits , {
 "Number of data bits excluding parity bit if present" , "gsm_a.dtap.number_of_data_bits" , FT_BOOLEAN , 8 , TFS ( & tfs_parity_bits ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_user_rate , {
 "User rate" , "gsm_a.dtap.user_rate" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_user_rate_vals ) , 0x0F , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_v110_x30_rate_adaptation , {
 "V.110/X.30 rate adaptation Intermediate rate" , "gsm_a.dtap.v110_x30_rate_adaptation" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_v110_x30_rate_adaptation_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_nic_on_tx , {
 "Network independent clock (NIC) on transmission (Tx)" , "gsm_a.dtap.nic_on_tx" , FT_BOOLEAN , 8 , TFS ( & tfs_nic_on_tx ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_nic_on_rx , {
 "Network independent clock (NIC) on reception (Rx)" , "gsm_a.dtap.nic_on_rx" , FT_BOOLEAN , 8 , TFS ( & tfs_nic_on_rx ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_parity_information , {
 "Parity information" , "gsm_a.dtap.parity_information" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_parity_info_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_connection_element , {
 "Connection element" , "gsm_a.dtap.connection_element" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_connection_element_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_modem_type , {
 "Modem type" , "gsm_a.dtap.modem_type" , FT_UINT8 , BASE_DEC , NULL , 0x1f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_other_modem_type , {
 "Other modem type" , "gsm_a.dtap.other_modem_type" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_other_modem_type_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_fixed_network_user_rate , {
 "Fixed network user rate" , "gsm_a.dtap.fixed_network_user_rate" , FT_UINT8 , BASE_DEC , NULL , 0x1f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_acceptable_channel_codings_TCH_F14_4 , {
 "Acceptable channel codings (TCH/F14.4)" , "gsm_a.dtap.acceptable_channel_codings.TCH_F14_4" , FT_BOOLEAN , 8 , TFS ( & tfs_acceptable_not_acceptable ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_acceptable_channel_codings_spare20 , {
 "Acceptable channel codings (Spare)" , "gsm_a.dtap.acceptable_channel_codings.spare" , FT_BOOLEAN , 8 , NULL , 0x20 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_acceptable_channel_codings_TCH_F9_6 , {
 "Acceptable channel codings (TCH/F9.6)" , "gsm_a.dtap.acceptable_channel_codings.TCH_F9_6" , FT_BOOLEAN , 8 , TFS ( & tfs_acceptable_not_acceptable ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_acceptable_channel_codings_TCH_F4_8 , {
 "Acceptable channel codings (TCH/F4.8)" , "gsm_a.dtap.acceptable_channel_codings.TCH_F4_8" , FT_BOOLEAN , 8 , TFS ( & tfs_acceptable_not_acceptable ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_maximum_number_of_traffic_channels , {
 "Maximum number of traffic channels" , "gsm_a.dtap.maximum_number_of_traffic_channels" , FT_UINT8 , BASE_DEC , NULL , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_acceptable_channel_codings_spare78 , {
 "Acceptable channel codings" , "gsm_a.dtap.acceptable_channel_codings" , FT_UINT8 , BASE_DEC , NULL , 0x78 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_uimi , {
 "UIMI, User initiated modification indication" , "gsm_a.dtap.uimi" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_uimi_vals ) , 0x70 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_wanted_air_interface_user_rate , {
 "Wanted air interface user rate" , "gsm_a.dtap.wanted_air_interface_user_rate" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_wanted_air_rate_vals ) , 0x0F , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_acceptable_channel_codings_ext_TCH_F28_8 , {
 "Acceptable channel codings extended (TCH/F28.8)" , "gsm_a.dtap.acceptable_channel_codings_ext.TCH_F28_8" , FT_BOOLEAN , 8 , TFS ( & tfs_acceptable_not_acceptable ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_acceptable_channel_codings_ext_TCH_F32_0 , {
 "Acceptable channel codings extended (TCH/F32.0)" , "gsm_a.dtap.acceptable_channel_codings_ext.TCH_F32_0" , FT_BOOLEAN , 8 , TFS ( & tfs_acceptable_not_acceptable ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_acceptable_channel_codings_ext_TCH_F43_2 , {
 "Acceptable channel codings extended (TCH/F43.2)" , "gsm_a.dtap.acceptable_channel_codings_ext.TCH_F43_2" , FT_BOOLEAN , 8 , TFS ( & tfs_acceptable_not_acceptable ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_channel_coding_asymmetry_indication , {
 "Channel Coding Asymmetry Indication" , "gsm_a.dtap.channel_coding_asymmetry_indication" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_channel_coding_asymmetry_ind_vals ) , 0x0c , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_edge_channel_codings , {
 "EDGE Channel Codings" , "gsm_a.dtap.edge_channel_codings" , FT_UINT8 , BASE_DEC , NULL , 0x7c , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_layer_2_identity , {
 "Layer 2 Identity" , "gsm_a.dtap.layer_2_identity" , FT_UINT8 , BASE_DEC , NULL , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_user_information_layer_2_protocol , {
 "User information layer 2 protocol" , "gsm_a.dtap.user_information_layer_2_protocol" , FT_UINT8 , BASE_DEC , NULL , 0x1f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_maximum_number_of_supported_bearers , {
 "Maximum number of supported bearers" , "gsm_a.dtap.maximum_number_of_supported_bearers" , FT_UINT8 , BASE_DEC , NULL , 0xf0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_pcp , {
 "Prolonged Clearing Procedure" , "gsm_a.dtap.pcp" , FT_BOOLEAN , 8 , TFS ( & tfs_supported_not_supported ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_dtmf , {
 "DTMF" , "gsm_a.dtap.dtmf" , FT_BOOLEAN , 8 , TFS ( & gsm_a_dtap_dtmf_value ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_max_num_of_speech_bearers , {
 "Maximum number of speech bearers" , "gsm_a.dtap.max_num_of_speech_bearers" , FT_UINT8 , BASE_DEC , NULL , 0x0f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_de_cause_coding_standard , {
 "Coding standard" , "gsm_a.dtap.coding_standard" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_de_cause_coding_standard_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_recommendation , {
 "Recommendation" , "gsm_a.dtap.recommendation" , FT_UINT8 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_data , {
 "Data" , "gsm_a.dtap.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_keypad_information , {
 "Keypad information" , "gsm_a.dtap.keypad_information" , FT_UINT8 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_repeat_indicator , {
 "Repeat Indicator" , "gsm_a.dtap.repeat_indicator" , FT_UINT8 , BASE_DEC , NULL , 0x0f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_ss_version_indicator , {
 "SS Version Indicator" , "gsm_a.dtap.ss_version_indicator" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_cp_cause , {
 "Cause" , "gsm_a.dtap.cp_cause" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_test_loop , {
 "Test Loop" , "gsm_a.dtap.test_loop" , FT_UINT8 , BASE_DEC , NULL , 0x3f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_subchannel , {
 "Subchannel" , "gsm_a.dtap.subchannel" , FT_BOOLEAN , 8 , TFS ( & tfs_gsm_a_dtap_subchannel ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_ack_element , {
 "Acknowledgment element" , "gsm_a.dtap.ack_element" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_channel_coding03 , {
 "Channel coding" , "gsm_a.dtap.channel_coding" , FT_UINT8 , BASE_DEC , VALS ( gsm_channel_coding_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_channel_coding30 , {
 "Channel coding" , "gsm_a.dtap.channel_coding" , FT_UINT8 , BASE_DEC , VALS ( gsm_channel_coding_vals ) , 0x30 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_loop_mechanism0E , {
 "Loop mechanism" , "gsm_a.dtap.loop_mechanism" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_loop_mech_vals ) , 0x0e , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_loop_mechanism1C , {
 "Loop mechanism" , "gsm_a.dtap.loop_mechanism" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_loop_mech_vals ) , 0x1c , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_multislot_tch , {
 "Multi-slot TCH loop" , "gsm_a.dtap.multislot_tch" , FT_BOOLEAN , 8 , TFS ( & tfs_multislot_tch ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_tp_tested_device , {
 "Tested device" , "gsm_a.dtap.tp_tested_device" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_tp_pdu_description , {
 "PDUs transmitted" , "gsm_a.dtap.tp_pdu_description" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_mode_flag , {
 "Mode flag" , "gsm_a.dtap.mode_flag" , FT_BOOLEAN , 8 , TFS ( & tfs_gsm_a_dtap_mode_flag ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_egprs_mode_flag , {
 "EGPRS Mode flag" , "gsm_a.dtap.egprs_mode_flag" , FT_BOOLEAN , 8 , TFS ( & tfs_gsm_a_dtap_egprs_mode_flag ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_downlink_timeslot_offset , {
 "Downlink Timeslot Offset" , "gsm_a.dtap.downlink_timeslot_offset" , FT_UINT8 , BASE_DEC , NULL , 0x0E , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_ms_positioning_technology , {
 "MS positioning technology" , "gsm_a.dtap.ms_positioning_technology" , FT_UINT8 , BASE_DEC , VALS ( gsm_positioning_technology_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_ue_test_loop_mode , {
 "UE test loop mode" , "gsm_a.dtap.ue_test_loop_mode" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_ue_test_loop_mode_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_ue_positioning_technology , {
 "UE positioning technology" , "gsm_a.dtap.ue_positioning_technology" , FT_UINT8 , BASE_DEC , VALS ( gsm_positioning_technology_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_ciphering_key_sequence_number , {
 "Ciphering Key Sequence Number" , "gsm_a.dtap.ciphering_key_sequence_number" , FT_UINT8 , BASE_DEC , NULL , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_ciphering_key_sequence_number70 , {
 "Ciphering Key Sequence Number" , "gsm_a.dtap.ciphering_key_sequence_number" , FT_UINT8 , BASE_DEC , NULL , 0x70 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_service_type , {
 "Service Type" , "gsm_a.dtap.service_type" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_service_type_vals ) , 0x0F , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_type_of_identity , {
 "Type of identity" , "gsm_a.dtap.type_of_identity" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_type_of_identity_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_follow_on_request , {
 "Follow-On Request (FOR)" , "gsm_a.dtap.follow_on_request" , FT_BOOLEAN , 8 , TFS ( & tfs_follow_on_request_value ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_updating_type , {
 "Updating Type" , "gsm_a.dtap.updating_type" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_dtap_updating_type_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_congestion_level , {
 "Congestion level" , "gsm_a.dtap.congestion_level" , FT_UINT8 , BASE_DEC , NULL , 0x0F , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_protocol_discriminator , {
 "Protocol Discriminator" , "gsm_a.dtap.protocol_discriminator" , FT_UINT8 , BASE_DEC , VALS ( protocol_discriminator_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_ti_flag , {
 "TI flag" , "gsm_a.dtap.ti_flag" , FT_BOOLEAN , 8 , TFS ( & tfs_allocated_by_receiver_sender ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_tio , {
 "TIO" , "gsm_a.dtap.tio" , FT_UINT8 , BASE_DEC , NULL , 0x70 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_tie , {
 "TIE" , "gsm_a.dtap.tie" , FT_UINT8 , BASE_DEC , NULL , DTAP_TIE_MASK , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_timeslot_number , {
 "Timeslot number" , "gsm_a_dtap.timeslot_number" , FT_UINT8 , BASE_DEC , NULL , 0xe0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_uplink_rlc_sdu_size , {
 "Uplink RLC SDU size" , "gsm_a_dtap.uplink_rlc_sdu_size" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_radio_bearer , {
 "Radio Bearer" , "gsm_a_dtap.radio_bearer" , FT_UINT8 , BASE_DEC , NULL , 0x1F , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_mbms_short_transmission_identity , {
 "MBMS short transmission identity" , "gsm_a_dtap.mbms_short_transmission_identity" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_ue_received_rlc_sdu_counter_value , {
 "UE received RLC SDU counter value" , "gsm_a_dtap.ue_received_rlc_sdu_counter_value" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtap_num_lb_entities , {
 "Number of LB entities" , "gsm_a_dtap.num_lb_entities" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , }
 ;

 static ei_register_info ei [ ] = {
 {
 & ei_gsm_a_dtap_autn , {
 "gsm_a.dtap.autn.invalid" , PI_MALFORMED , PI_WARN , "AUTN length not equal to 16" , EXPFILL }
 }
 , {
 & ei_gsm_a_dtap_auts , {
 "gsm_a.dtap.auts.invalid" , PI_MALFORMED , PI_WARN , "AUTS length not equal to 14" , EXPFILL }
 }
 , {
 & ei_gsm_a_dtap_text_string_not_multiple_of_7 , {
 "gsm_a.dtap.text_string_not_multiple_of_7" , PI_MALFORMED , PI_WARN , "Value leads to a Text String whose length is not a multiple of 7 bits" , EXPFILL }
 }
 , {
 & ei_gsm_a_dtap_not_digit , {
 "gsm_a.dtap.not_digit" , PI_MALFORMED , PI_WARN , "BCD number contains a value that is not a digit" , EXPFILL }
 }
 , {
 & ei_gsm_a_dtap_end_mark_unexpected , {
 "gsm_a.dtap.end_mark_unexpected" , PI_MALFORMED , PI_WARN , "\'f\' end mark present in unexpected position" , EXPFILL }
 }
 , {
 & ei_gsm_a_dtap_invalid_ia5_character , {
 "gsm_a.dtap.invalid_ia5_character" , PI_MALFORMED , PI_WARN , "Invalid IA5 character(s) in string (value > 127)" , EXPFILL }
 }
 , {
 & ei_gsm_a_dtap_keypad_info_not_dtmf_digit , {
 "gsm_a.dtap.keypad_info_not_dtmf_digit" , PI_MALFORMED , PI_WARN , "Keypad information contains character that is not a DTMF digit" , EXPFILL }
 }
 , {
 & ei_gsm_a_dtap_extraneous_data , {
 "gsm_a.dtap.extraneous_data" , PI_PROTOCOL , PI_NOTE , "Extraneous Data, dissector bug or later version spec(report to wireshark.org)" , EXPFILL }
 }
 , {
 & ei_gsm_a_dtap_missing_mandatory_element , {
 "gsm_a.dtap.missing_mandatory_element" , PI_PROTOCOL , PI_WARN , "Missing Mandatory element, rest of dissection is suspect" , EXPFILL }
 }
 , {
 & ei_gsm_a_dtap_coding_scheme , {
 "gsm_a.dtap.coding_scheme.unknown" , PI_PROTOCOL , PI_WARN , "Text string encoded according to an unknown Coding Scheme" , EXPFILL }
 }
 , }
 ;
 expert_module_t * expert_a_dtap ;
 ett [ 0 ] = & ett_dtap_msg ;
 ett [ 1 ] = & ett_dtap_oct_1 ;
 ett [ 2 ] = & ett_cm_srvc_type ;
 ett [ 3 ] = & ett_gsm_enc_info ;
 ett [ 4 ] = & ett_bc_oct_3 ;
 ett [ 5 ] = & ett_bc_oct_3a ;
 ett [ 6 ] = & ett_bc_oct_4 ;
 ett [ 7 ] = & ett_bc_oct_5 ;
 ett [ 8 ] = & ett_bc_oct_5a ;
 ett [ 9 ] = & ett_bc_oct_5b ;
 ett [ 10 ] = & ett_bc_oct_6 ;
 ett [ 11 ] = & ett_bc_oct_6a ;
 ett [ 12 ] = & ett_bc_oct_6b ;
 ett [ 13 ] = & ett_bc_oct_6c ;
 ett [ 14 ] = & ett_bc_oct_6d ;
 ett [ 15 ] = & ett_bc_oct_6e ;
 ett [ 16 ] = & ett_bc_oct_6f ;
 ett [ 17 ] = & ett_bc_oct_6g ;
 ett [ 18 ] = & ett_bc_oct_7 ;
 ett [ 19 ] = & ett_epc_ue_tl_a_lb_setup ;
 ett [ 20 ] = & ett_mm_timer ;
 ett [ 21 ] = & ett_ue_test_loop_mode ;
 last_offset = NUM_INDIVIDUAL_ELEMS ;
 for ( i = 0 ;
 i < NUM_GSM_DTAP_MSG_MM ;
 i ++ , last_offset ++ ) {
 ett_gsm_dtap_msg_mm [ i ] = - 1 ;
 ett [ last_offset ] = & ett_gsm_dtap_msg_mm [ i ] ;
 }
 for ( i = 0 ;
 i < NUM_GSM_DTAP_MSG_CC ;
 i ++ , last_offset ++ ) {
 ett_gsm_dtap_msg_cc [ i ] = - 1 ;
 ett [ last_offset ] = & ett_gsm_dtap_msg_cc [ i ] ;
 }
 for ( i = 0 ;
 i < NUM_GSM_DTAP_MSG_SMS ;
 i ++ , last_offset ++ ) {
 ett_gsm_dtap_msg_sms [ i ] = - 1 ;
 ett [ last_offset ] = & ett_gsm_dtap_msg_sms [ i ] ;
 }
 for ( i = 0 ;
 i < NUM_GSM_DTAP_MSG_SS ;
 i ++ , last_offset ++ ) {
 ett_gsm_dtap_msg_ss [ i ] = - 1 ;
 ett [ last_offset ] = & ett_gsm_dtap_msg_ss [ i ] ;
 }
 for ( i = 0 ;
 i < NUM_GSM_DTAP_MSG_TP ;
 i ++ , last_offset ++ ) {
 ett_gsm_dtap_msg_tp [ i ] = - 1 ;
 ett [ last_offset ] = & ett_gsm_dtap_msg_tp [ i ] ;
 }
 for ( i = 0 ;
 i < NUM_GSM_DTAP_ELEM ;
 i ++ , last_offset ++ ) {
 ett_gsm_dtap_elem [ i ] = - 1 ;
 ett [ last_offset ] = & ett_gsm_dtap_elem [ i ] ;
 }
 proto_a_dtap = proto_register_protocol ( "GSM A-I/F DTAP" , "GSM DTAP" , "gsm_a.dtap" ) ;
 proto_register_field_array ( proto_a_dtap , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_a_dtap = expert_register_protocol ( proto_a_dtap ) ;
 expert_register_field_array ( expert_a_dtap , ei , array_length ( ei ) ) ;
 register_dissector ( "gsm_a_dtap" , dissect_dtap , proto_a_dtap ) ;
 u2u_dissector_table = register_dissector_table ( "gsm_a.dtap.u2u_prot_discr" , "GSM User to User Signalling" , proto_a_dtap , FT_UINT8 , BASE_DEC ) ;
 }