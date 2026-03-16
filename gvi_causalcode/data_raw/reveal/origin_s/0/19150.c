void proto_register_rsl ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_rsl_msg_dsc , {
 "Message discriminator" , "gsm_abis_rsl.msg_dsc" , FT_UINT8 , BASE_DEC , VALS ( rsl_msg_disc_vals ) , 0xfe , NULL , HFILL }
 }
 , {
 & hf_rsl_T_bit , {
 "T bit" , "gsm_abis_rsl.T_bit" , FT_BOOLEAN , 8 , TFS ( & rsl_t_bit_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsl_msg_type , {
 "Message type" , "gsm_abis_rsl.msg_type" , FT_UINT8 , BASE_HEX_DEC | BASE_EXT_STRING , & rsl_msg_type_vals_ext , 0x7f , NULL , HFILL }
 }
 , {
 & hf_rsl_ie_id , {
 "Element identifier" , "gsm_abis_rsl.ie_id" , FT_UINT8 , BASE_HEX_DEC | BASE_EXT_STRING , & rsl_ie_type_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_ie_length , {
 "Length" , "gsm_abis_rsl.ie_length" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_ch_no_Cbits , {
 "C-bits" , "gsm_abis_rsl.ch_no_Cbits" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & rsl_ch_no_Cbits_vals_ext , 0xf8 , NULL , HFILL }
 }
 , {
 & hf_rsl_ch_no_TN , {
 "Time slot number (TN)" , "gsm_abis_rsl.ch_no_TN" , FT_UINT8 , BASE_DEC , NULL , 0x07 , NULL , HFILL }
 }
 , {
 & hf_rsl_rtd , {
 "Round Trip Delay (RTD)" , "gsm_abis_rsl.rtd" , FT_UINT8 , BASE_DEC , NULL , 0xfe , NULL , HFILL }
 }
 , {
 & hf_rsl_delay_ind , {
 "Delay IND" , "gsm_abis_rsl.delay_ind" , FT_UINT8 , BASE_DEC , VALS ( rsl_delay_ind_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsl_tfo , {
 "TFO" , "gsm_abis_rsl.tfo" , FT_BOOLEAN , 8 , TFS ( & rsl_tfo_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsl_req_ref_ra , {
 "Random Access Information (RA)" , "gsm_abis_rsl.req_ref_ra" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_req_ref_T1prim , {
 "T1'" , "gsm_abis_rsl.req_ref_T1prim" , FT_UINT8 , BASE_DEC , NULL , 0xf8 , NULL , HFILL }
 }
 , {
 & hf_rsl_req_ref_T3 , {
 "T3" , "gsm_abis_rsl.req_ref_T3" , FT_UINT16 , BASE_DEC , NULL , 0x07e0 , NULL , HFILL }
 }
 , {
 & hf_rsl_req_ref_T2 , {
 "T2" , "gsm_abis_rsl.req_ref_T2" , FT_UINT8 , BASE_DEC , NULL , 0x1f , NULL , HFILL }
 }
 , {
 & hf_rsl_timing_adv , {
 "Timing Advance" , "gsm_abis_rsl.timing_adv" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_ho_ref , {
 "Hand-over reference" , "gsm_abis_rsl.ho_ref" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_l1inf_power_lev , {
 "MS power level" , "gsm_abis_rsl.ms_power_lev" , FT_UINT8 , BASE_DEC , NULL , 0xf8 , NULL , HFILL }
 }
 , {
 & hf_rsl_l1inf_fpc , {
 "FPC/EPC" , "gsm_abis_rsl.ms_fpc" , FT_BOOLEAN , 8 , TFS ( & rsl_ms_fpc_epc_mode_vals ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_rsl_ms_power_lev , {
 "MS power level" , "gsm_abis_rsl.ms_power_lev" , FT_UINT8 , BASE_DEC , NULL , 0x1f , NULL , HFILL }
 }
 , {
 & hf_rsl_ms_fpc , {
 "FPC/EPC" , "gsm_abis_rsl.ms_fpc" , FT_BOOLEAN , 8 , TFS ( & rsl_ms_fpc_epc_mode_vals ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_rsl_act_timing_adv , {
 "Actual Timing Advance" , "gsm_abis_rsl.act_timing_adv" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_dtxd , {
 "DTXd" , "gsm_abis_rsl.dtxd" , FT_BOOLEAN , 8 , TFS ( & rsl_dtxd_vals ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_rsl_rxlev_full_up , {
 "RXLEV.FULL.up" , "gsm_abis_rsl.rxlev_full_up" , FT_UINT8 , BASE_DEC , NULL , 0x3f , NULL , HFILL }
 }
 , {
 & hf_rsl_rxlev_sub_up , {
 "RXLEV.SUB.up" , "gsm_abis_rsl.rxlev_sub_up" , FT_UINT8 , BASE_DEC , NULL , 0x3f , NULL , HFILL }
 }
 , {
 & hf_rsl_rxqual_full_up , {
 "RXQUAL.FULL.up" , "gsm_abis_rsl.rxqual_full_up" , FT_UINT8 , BASE_DEC , NULL , 0x38 , NULL , HFILL }
 }
 , {
 & hf_rsl_rxqual_sub_up , {
 "RXQUAL.SUB.up" , "gsm_abis_rsl.rxqual_sub_up" , FT_UINT8 , BASE_DEC , NULL , 0x07 , NULL , HFILL }
 }
 , {
 & hf_rsl_acc_delay , {
 "Access Delay" , "gsm_abis_rsl.acc_del" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_rach_slot_cnt , {
 "RACH Slot Count" , "gsm_abis_rsl.rach_slot_cnt" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_rach_busy_cnt , {
 "RACH Busy Count" , "gsm_abis_rsl.rach_busy_cnt" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_rach_acc_cnt , {
 "RACH Access Count" , "gsm_abis_rsl.rach_acc_cnt" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_phy_ctx , {
 "Physical Context" , "gsm_abis_rsl.phy_ctx" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_na , {
 "Not applicable (NA)" , "gsm_abis_rsl.na" , FT_BOOLEAN , 8 , TFS ( & rsl_na_vals ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_rsl_ch_type , {
 "channel type" , "gsm_abis_rsl.ch_type" , FT_UINT8 , BASE_DEC , VALS ( rsl_ch_type_vals ) , 0xc0 , NULL , HFILL }
 }
 , {
 & hf_rsl_prio , {
 "Priority" , "gsm_abis_rsl.prio" , FT_UINT8 , BASE_DEC , VALS ( rsl_prio_vals ) , 0x18 , NULL , HFILL }
 }
 , {
 & hf_rsl_sapi , {
 "SAPI" , "gsm_abis_rsl.sapi" , FT_UINT8 , BASE_DEC , NULL , 0x07 , NULL , HFILL }
 }
 , {
 & hf_rsl_rbit , {
 "R" , "gsm_abis_rsl.rbit" , FT_BOOLEAN , 8 , TFS ( & rsl_rbit_vals ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsl_a3a2 , {
 "A3A2" , "gsm_abis_rsl.a3a2" , FT_UINT8 , BASE_DEC , VALS ( rsl_a3a2_vals ) , 0x06 , NULL , HFILL }
 }
 , {
 & hf_rsl_a1_0 , {
 "A1" , "gsm_abis_rsl.a1_0" , FT_BOOLEAN , 8 , TFS ( & rsl_a1_0_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsl_a1_1 , {
 "A1" , "gsm_abis_rsl.a1_1" , FT_BOOLEAN , 8 , TFS ( & rsl_a1_1_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsl_a1_2 , {
 "A1" , "gsm_abis_rsl.a2_0" , FT_BOOLEAN , 8 , TFS ( & rsl_a1_2_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsl_epc_mode , {
 "EPC mode" , "gsm_abis_rsl.epc_mode" , FT_BOOLEAN , 8 , TFS ( & rsl_epc_mode_vals ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_rsl_bs_fpc_epc_mode , {
 "FPC-EPC mode" , "gsm_abis_rsl.fpc_epc_mode" , FT_BOOLEAN , 8 , TFS ( & rsl_fpc_epc_mode_vals ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_rsl_bs_power , {
 "Power Level" , "gsm_abis_rsl.bs_power" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & rsl_rlm_bs_power_vals_ext , 0x0f , NULL , HFILL }
 }
 , {
 & hf_rsl_cm_dtxd , {
 "DTXd" , "gsm_abis_rsl.cm_dtxd" , FT_BOOLEAN , 8 , TFS ( & rsl_dtx_vals ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_rsl_cm_dtxu , {
 "DTXu" , "gsm_abis_rsl.cm_dtxu" , FT_BOOLEAN , 8 , TFS ( & rsl_dtx_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsl_speech_or_data , {
 "Speech or data indicator" , "gsm_abis_rsl.speech_or_data" , FT_UINT8 , BASE_DEC , VALS ( rsl_speech_or_data_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_ch_rate_and_type , {
 "Channel rate and type" , "gsm_abis_rsl.ch_rate_and_type" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & rsl_ch_rate_and_type_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_speech_coding_alg , {
 "Speech coding algorithm" , "gsm_abis_rsl.speech_coding_alg" , FT_UINT8 , BASE_DEC , VALS ( rsl_speech_coding_alg_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_t_nt_bit , {
 "Transparent indication" , "gsm_abis_rsl.t_nt_bit" , FT_BOOLEAN , 8 , TFS ( & t_nt_bit_vals ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_rsl_ra_if_data_rte , {
 "Radio interface data rate" , "gsm_abis_rsl.ra_if_data_rte" , FT_UINT8 , BASE_DEC , VALS ( rsl_ra_if_data_rte_vals ) , 0x3f , NULL , HFILL }
 }
 , {
 & hf_rsl_data_rte , {
 "Data rate" , "gsm_abis_rsl.data_rte" , FT_UINT8 , BASE_DEC , VALS ( rsl_ra_if_data_rte_vals ) , 0x3f , NULL , HFILL }
 }
 , {
 & hf_rsl_alg_id , {
 "Algorithm Identifier" , "gsm_abis_rsl.alg_id" , FT_UINT8 , BASE_DEC , VALS ( rsl_algorithm_id_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_key , {
 "KEY" , "gsm_abis_rsl.key" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_cause , {
 "Cause" , "gsm_abis_rsl.cause" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & rsl_rlm_cause_vals_ext , 0x7f , NULL , HFILL }
 }
 , {
 & hf_rsl_rel_mode , {
 "Release Mode" , "gsm_abis_rsl.rel_mode" , FT_UINT8 , BASE_DEC , VALS ( rel_mode_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_rsl_interf_band , {
 "Interf Band" , "gsm_abis_rsl.interf_band" , FT_UINT8 , BASE_DEC , NULL , 0xe0 , NULL , HFILL }
 }
 , {
 & hf_rsl_interf_band_reserved , {
 "Interf Band reserved bits" , "gsm_abis_rsl.interf_band_reserved" , FT_UINT8 , BASE_DEC , NULL , 0x1f , NULL , HFILL }
 }
 , {
 & hf_rsl_meas_res_no , {
 "Measurement result number" , "gsm_abis_rsl.meas_res_no" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_extension_bit , {
 "Extension" , "gsm_abis_rsl.extension_bit" , FT_BOOLEAN , 8 , TFS ( & rsl_extension_bit_value ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsl_class , {
 "Class" , "gsm_abis_rsl.class" , FT_UINT8 , BASE_DEC , VALS ( rsl_class_vals ) , 0x70 , NULL , HFILL }
 }
 , {
 & hf_rsl_paging_grp , {
 "Paging Group" , "gsm_abis_rsl.paging_grp" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_paging_load , {
 "Paging Buffer Space" , "gsm_abis_rsl.paging_load" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_sys_info_type , {
 "System Info Type" , "gsm_abis_rsl.sys_info_type" , FT_UINT8 , BASE_DEC | BASE_EXT_STRING , & rsl_sys_info_type_vals_ext , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_timing_offset , {
 "Timing Offset" , "gsm_abis_rsl.timing_offset" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_ch_needed , {
 "Channel Needed" , "gsm_abis_rsl.ch_needed" , FT_UINT8 , BASE_DEC , VALS ( rsl_ch_needed_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_rsl_cbch_load_type , {
 "CBCH Load Type" , "gsm_abis_rsl.cbch_load_type" , FT_BOOLEAN , 8 , TFS ( & rsl_cbch_load_type_vals ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_rsl_msg_slt_cnt , {
 "Message Slot Count" , "gsm_abis_rsl.sg_slt_cnt" , FT_UINT8 , BASE_DEC , NULL , 0x0f , NULL , HFILL }
 }
 , {
 & hf_rsl_ch_ind , {
 "Channel Ind" , "gsm_abis_rsl.ch_ind" , FT_UINT8 , BASE_DEC , VALS ( rsl_ch_ind_vals ) , 0x0f , NULL , HFILL }
 }
 , {
 & hf_rsl_command , {
 "Command" , "gsm_abis_rsl.cmd" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_emlpp_prio , {
 "eMLPP Priority" , "gsm_abis_rsl.emlpp_prio" , FT_UINT8 , BASE_DEC , VALS ( rsl_emlpp_prio_vals ) , 0x03 , NULL , HFILL }
 }
 , {
 & hf_rsl_speech_mode_s , {
 "ip.access Speech Mode S" , "gsm_abis_rsl.ipacc.speech_mode_s" , FT_UINT8 , BASE_HEX , VALS ( rsl_ipacc_spm_s_vals ) , 0xf , NULL , HFILL }
 }
 , {
 & hf_rsl_speech_mode_m , {
 "ip.access Speech Mode M" , "gsm_abis_rsl.ipacc.speech_mode_m" , FT_UINT8 , BASE_HEX , VALS ( rsl_ipacc_spm_m_vals ) , 0xf0 , NULL , HFILL }
 }
 , {
 & hf_rsl_conn_id , {
 "ip.access Connection ID" , "gsm_abis_rsl.ipacc.conn_id" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_rtp_payload , {
 "ip.access RTP Payload Type" , "gsm_abis_rsl.ipacc.rtp_payload" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_rtp_csd_fmt_d , {
 "ip.access RTP CSD Format D" , "gsm_abis_rsl.ipacc.rtp_csd_fmt_d" , FT_UINT8 , BASE_HEX , VALS ( rsl_ipacc_rtp_csd_fmt_d_vals ) , 0x0f , NULL , HFILL }
 , }
 , {
 & hf_rsl_rtp_csd_fmt_ir , {
 "ip.access RTP CSD Format IR" , "gsm_abis_rsl.ipacc.rtp_csd_fmt_ir" , FT_UINT8 , BASE_HEX , VALS ( rsl_ipacc_rtp_csd_fmt_ir_vals ) , 0xf0 , NULL , HFILL }
 , }
 , {
 & hf_rsl_local_port , {
 "ip.access Local RTP Port" , "gsm_abis_rsl.ipacc.local_port" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 , }
 , {
 & hf_rsl_remote_port , {
 "ip.access Remote RTP Port" , "gsm_abis_rsl.ipacc.remote_port" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 , }
 , {
 & hf_rsl_local_ip , {
 "ip.access Local IP Address" , "gsm_abis_rsl.ipacc.local_ip" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 , }
 , {
 & hf_rsl_remote_ip , {
 "ip.access Remote IP Address" , "gsm_abis_rsl.ipacc.remote_ip" , FT_IPv4 , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 , }
 , {
 & hf_rsl_cstat_tx_pkts , {
 "Packets Sent" , "gsm_abis_rsl.ipacc.cstat.tx_pkts" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsl_cstat_tx_octs , {
 "Octets Sent" , "gsm_abis_rsl.ipacc.cstat.tx_octets" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsl_cstat_rx_pkts , {
 "Packets Received" , "gsm_abis_rsl.ipacc.cstat.rx_pkts" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsl_cstat_rx_octs , {
 "Octets Received" , "gsm_abis_rsl.ipacc.cstat.rx_octets" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsl_cstat_lost_pkts , {
 "Packets Lost" , "gsm_abis_rsl.ipacc.cstat.lost_pkts" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsl_cstat_ia_jitter , {
 "Inter-arrival Jitter" , "gsm_abis_rsl.ipacc.cstat.ia_jitter" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsl_cstat_avg_tx_dly , {
 "Average Tx Delay" , "gsm_abis_rsl.ipacc.cstat.avg_tx_delay" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_rsl_channel_description_tag , {
 "Channel Description Tag" , "gsm_abis_rsl.channel_description_tag" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_mobile_allocation_tag , {
 "Mobile Allocation Tag+Length(0)" , "gsm_abis_rsl.mobile_allocation_tag" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_no_resources_required , {
 "0 No resources required(All other values are reserved)" , "gsm_abis_rsl.no_resources_required" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_llsdu_ccch , {
 "Link Layer Service Data Unit (L3 Message)(CCCH)" , "gsm_abis_rsl.llsdu.ccch" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_llsdu_sacch , {
 "Link Layer Service Data Unit (L3 Message)(SACCH)" , "gsm_abis_rsl.llsdu.sacch" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_llsdu , {
 "Link Layer Service Data Unit (L3 Message)" , "gsm_abis_rsl.llsdu" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_rach_supplementary_information , {
 "Supplementary Information" , "gsm_abis_rsl.supplementary_information" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_full_immediate_assign_info_field , {
 "Full Immediate Assign Info field" , "gsm_abis_rsl.full_immediate_assign_info_field" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_layer_3_message , {
 "Layer 3 message" , "gsm_abis_rsl.layer_3_message" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_descriptive_group_or_broadcast_call_reference , {
 "Descriptive group or broadcast call reference" , "gsm_abis_rsl.descriptive_group_or_broadcast_call_reference" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_group_channel_description , {
 "Group Channel Description" , "gsm_abis_rsl.group_channel_description" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_uic , {
 "UIC" , "gsm_abis_rsl.uic" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_rsl_codec_list , {
 "Codec List" , "gsm_abis_rsl.codec_list" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_rsl , & ett_ie_link_id , & ett_ie_act_type , & ett_ie_bs_power , & ett_ie_ch_id , & ett_ie_ch_mode , & ett_ie_enc_inf , & ett_ie_ch_no , & ett_ie_frame_no , & ett_ie_ho_ref , & ett_ie_l1_inf , & ett_ie_L3_inf , & ett_ie_ms_id , & ett_ie_ms_pow , & ett_ie_phy_ctx , & ett_ie_paging_grp , & ett_ie_paging_load , & ett_ie_access_delay , & ett_ie_rach_load , & ett_ie_req_ref , & ett_ie_rel_mode , & ett_ie_resource_inf , & ett_ie_rlm_cause , & ett_ie_staring_time , & ett_ie_timing_adv , & ett_ie_uplink_meas , & ett_ie_full_imm_ass_inf , & ett_ie_smscb_inf , & ett_ie_ms_timing_offset , & ett_ie_err_msg , & ett_ie_full_bcch_inf , & ett_ie_ch_needed , & ett_ie_cb_cmd_type , & ett_ie_smscb_mess , & ett_ie_cbch_load_inf , & ett_ie_smscb_ch_ind , & ett_ie_grp_call_ref , & ett_ie_ch_desc , & ett_ie_nch_drx , & ett_ie_cmd_ind , & ett_ie_emlpp_prio , & ett_ie_uic , & ett_ie_main_ch_ref , & ett_ie_multirate_conf , & ett_ie_multirate_cntrl , & ett_ie_sup_codec_types , & ett_ie_codec_conf , & ett_ie_rtd , & ett_ie_tfo_status , & ett_ie_llp_apdu , & ett_ie_tfo_transp_cont , & ett_ie_cause , & ett_ie_meas_res_no , & ett_ie_message_id , & ett_ie_sys_info_type , & ett_ie_speech_mode , & ett_ie_conn_id , & ett_ie_remote_ip , & ett_ie_remote_port , & ett_ie_local_port , & ett_ie_local_ip , & ett_ie_rtp_payload , }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_rsl_speech_or_data_indicator , {
 "gsm_abis_rsl.speech_or_data_indicator.bad" , PI_PROTOCOL , PI_WARN , "Speech or data indicator != 1,2 or 3" , EXPFILL }
 }
 , {
 & ei_rsl_facility_information_element_3gpp_ts_44071 , {
 "gsm_abis_rsl.facility_information_element_3gpp_ts_44071" , PI_PROTOCOL , PI_NOTE , "Facility Information Element as defined in 3GPP TS 44.071" , EXPFILL }
 }
 , {
 & ei_rsl_embedded_message_tfo_configuration , {
 "gsm_abis_rsl.embedded_message_tfo_configuration" , PI_PROTOCOL , PI_NOTE , "Embedded message that contains the TFO configuration" , EXPFILL }
 }
 , }
 ;
 module_t * rsl_module ;
 expert_module_t * expert_rsl ;

 \ rsl_att_tlvdef . def [ _attr ] . fixed_len = _fixed_len ;
 RSL_ATT_TLVDEF ( RSL_IE_CH_NO , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_LINK_ID , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_ACT_TYPE , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_BS_POW , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_CH_ID , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_CH_MODE , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_ENC_INF , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_FRAME_NO , TLV_TYPE_FIXED , 2 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_HO_REF , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_L1_INF , TLV_TYPE_FIXED , 2 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_L3_INF , TLV_TYPE_TL16V , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_MS_ID , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_MS_POW , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_PAGING_GRP , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_PAGING_LOAD , TLV_TYPE_FIXED , 2 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_PHY_CTX , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_ACCESS_DELAY , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_RACH_LOAD , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_REQ_REF , TLV_TYPE_FIXED , 3 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_REL_MODE , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_RESOURCE_INF , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_RLM_CAUSE , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_STARTING_TIME , TLV_TYPE_FIXED , 2 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_TIMING_ADV , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_UPLINK_MEAS , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_CAUSE , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_MEAS_RES_NO , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_MESSAGE_ID , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_SYS_INFO_TYPE , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_MS_POWER_PARAM , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_BS_POWER_PARAM , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_PREPROC_PARAM , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_PREPROC_MEAS , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_ERR_MSG , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_FULL_BCCH_INF , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_CH_NEEDED , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_CB_CMD_TYPE , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_SMSCB_MESS , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_FULL_IMM_ASS_INF , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_CBCH_LOAD_INF , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_SMSCB_CH_IND , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_GRP_CALL_REF , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_CH_DESC , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_NCH_DRX_INF , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_CMD_IND , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_EMLPP_PRIO , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_UIC , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_MAIN_CH_REF , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_MULTIRATE_CONF , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_MULTIRATE_CNTRL , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_SUP_CODEC_TYPES , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_CODEC_CONF , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_RTD , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_TFO_STATUS , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_LLP_APDU , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_IPAC_REMOTE_IP , TLV_TYPE_FIXED , 4 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_IPAC_REMOTE_PORT , TLV_TYPE_FIXED , 2 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_IPAC_LOCAL_IP , TLV_TYPE_FIXED , 4 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_IPAC_CONN_STAT , TLV_TYPE_TLV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_IPAC_LOCAL_PORT , TLV_TYPE_FIXED , 2 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_IPAC_SPEECH_MODE , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_IPAC_CONN_ID , TLV_TYPE_FIXED , 2 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_IPAC_RTP_PAYLOAD2 , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_IPAC_RTP_PAYLOAD , TLV_TYPE_TV , 0 ) ;
 RSL_ATT_TLVDEF ( RSL_IE_IPAC_RTP_CSD_FMT , TLV_TYPE_TV , 0 ) ;
 proto_rsl = proto_register_protocol ( "Radio Signalling Link (RSL)" , "RSL" , "gsm_abis_rsl" ) ;
 proto_register_field_array ( proto_rsl , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_rsl = expert_register_protocol ( proto_rsl ) ;
 expert_register_field_array ( expert_rsl , ei , array_length ( ei ) ) ;
 register_dissector ( "gsm_abis_rsl" , dissect_rsl , proto_rsl ) ;
 rsl_module = prefs_register_protocol ( proto_rsl , proto_reg_handoff_rsl ) ;
 prefs_register_bool_preference ( rsl_module , "use_ipaccess_rsl" , "Use nanoBTS definitions" , "Use ipaccess nanoBTS specific definitions for RSL" , & global_rsl_use_nano_bts ) ;
 }