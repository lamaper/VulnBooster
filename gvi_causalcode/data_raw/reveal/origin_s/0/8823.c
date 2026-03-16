void proto_register_gsm_a_common ( void ) {
 guint i ;
 guint last_offset ;
 static hf_register_info hf [ ] = {
 {
 & hf_gsm_a_common_elem_id , {
 "Element ID" , "gsm_a.common.elem_id" , FT_UINT8 , BASE_HEX , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_common_elem_id_f0 , {
 "Element ID" , "gsm_a.common.elem_id" , FT_UINT8 , BASE_HEX , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_l_ext , {
 "ext" , "gsm_a.l_ext" , FT_UINT8 , BASE_DEC , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_tmsi , {
 "TMSI/P-TMSI" , "gsm_a.tmsi" , FT_UINT32 , BASE_HEX , 0 , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_imei , {
 "IMEI" , "gsm_a.imei" , FT_STRING , BASE_NONE , 0 , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_imeisv , {
 "IMEISV" , "gsm_a.imeisv" , FT_STRING , BASE_NONE , 0 , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_MSC_rev , {
 "Revision Level" , "gsm_a.MSC_rev" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_msc_rev_vals ) , 0x60 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ES_IND , {
 "ES IND" , "gsm_a.ES_IND" , FT_BOOLEAN , 8 , TFS ( & ES_IND_vals ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_A5_1_algorithm_sup , {
 "A5/1 algorithm supported" , "gsm_a.A5_1_algorithm_sup" , FT_BOOLEAN , 8 , TFS ( & A5_1_algorithm_sup_vals ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_RF_power_capability , {
 "RF Power Capability" , "gsm_a.RF_power_capability" , FT_UINT8 , BASE_DEC , VALS ( RF_power_capability_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ps_sup_cap , {
 "PS capability (pseudo-synchronization capability)" , "gsm_a.ps_sup_cap" , FT_BOOLEAN , 8 , TFS ( & ps_sup_cap_vals ) , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_SS_screening_indicator , {
 "SS Screening Indicator" , "gsm_a.SS_screening_indicator" , FT_UINT8 , BASE_DEC , VALS ( SS_screening_indicator_vals ) , 0x30 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_SM_capability , {
 "SM capability (MT SMS pt to pt capability)" , "gsm_a.SM_cap" , FT_BOOLEAN , 8 , TFS ( & SM_capability_vals ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_VBS_notification_rec , {
 "VBS notification reception" , "gsm_a.VBS_notification_rec" , FT_BOOLEAN , 8 , TFS ( & VBS_notification_rec_vals ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_VGCS_notification_rec , {
 "VGCS notification reception" , "gsm_a.VGCS_notification_rec" , FT_BOOLEAN , 8 , TFS ( & VGCS_notification_rec_vals ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_FC_frequency_cap , {
 "FC Frequency Capability" , "gsm_a.FC_frequency_cap" , FT_BOOLEAN , 8 , TFS ( & FC_frequency_cap_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_CM3 , {
 "CM3" , "gsm_a.CM3" , FT_BOOLEAN , 8 , TFS ( & CM3_vals ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_LCS_VA_cap , {
 "LCS VA capability (LCS value added location request notification capability)" , "gsm_a.LCS_VA_cap" , FT_BOOLEAN , 8 , TFS ( & LCS_VA_cap_vals ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_UCS2_treatment , {
 "UCS2 treatment" , "gsm_a.UCS2_treatment" , FT_BOOLEAN , 8 , TFS ( & UCS2_treatment_vals ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_SoLSA , {
 "SoLSA" , "gsm_a.SoLSA" , FT_BOOLEAN , 8 , TFS ( & SoLSA_vals ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_CMSP , {
 "CMSP: CM Service Prompt" , "gsm_a.CMSP" , FT_BOOLEAN , 8 , TFS ( & CMSP_vals ) , 0x04 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_A5_7_algorithm_sup , {
 "A5/7 algorithm supported" , "gsm_a.A5_7_algorithm_sup" , FT_BOOLEAN , BASE_NONE , TFS ( & A5_7_algorithm_sup_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_A5_6_algorithm_sup , {
 "A5/6 algorithm supported" , "gsm_a.A5_6_algorithm_sup" , FT_BOOLEAN , BASE_NONE , TFS ( & A5_6_algorithm_sup_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_A5_5_algorithm_sup , {
 "A5/5 algorithm supported" , "gsm_a.A5_5_algorithm_sup" , FT_BOOLEAN , BASE_NONE , TFS ( & A5_5_algorithm_sup_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_A5_4_algorithm_sup , {
 "A5/4 algorithm supported" , "gsm_a.A5_4_algorithm_sup" , FT_BOOLEAN , BASE_NONE , TFS ( & A5_4_algorithm_sup_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_A5_3_algorithm_sup , {
 "A5/3 algorithm supported" , "gsm_a.A5_3_algorithm_sup" , FT_BOOLEAN , 8 , TFS ( & A5_3_algorithm_sup_vals ) , 0x02 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_A5_2_algorithm_sup , {
 "A5/2 algorithm supported" , "gsm_a.A5_2_algorithm_sup" , FT_BOOLEAN , 8 , TFS ( & A5_2_algorithm_sup_vals ) , 0x01 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_mobile_identity_type , {
 "Mobile Identity Type" , "gsm_a.ie.mobileid.type" , FT_UINT8 , BASE_DEC , VALS ( mobile_identity_type_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_id_dig_1 , {
 "Identity Digit 1" , "gsm_a.id_dig_1" , FT_UINT8 , BASE_DEC , NULL , 0xf0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_odd_even_ind , {
 "Odd/even indication" , "gsm_a.oddevenind" , FT_BOOLEAN , 8 , TFS ( & oddevenind_vals ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_unused , {
 "Unused" , "gsm_a.unused" , FT_UINT8 , BASE_HEX , NULL , 0xf0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_tmgi_mcc_mnc_ind , {
 "MCC/MNC indication" , "gsm_a.tmgi_mcc_mnc_ind" , FT_BOOLEAN , 8 , TFS ( & gsm_a_present_vals ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_mbs_ses_id_ind , {
 "MBMS Session Identity indication" , "gsm_a.mbs_session_id_ind" , FT_BOOLEAN , 8 , TFS ( & gsm_a_present_vals ) , 0x20 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_mbs_service_id , {
 "MBMS Service ID" , "gsm_a.mbs_service_id" , FT_UINT24 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_mbs_session_id , {
 "MBMS Session ID" , "gsm_a.mbs_session_id" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_length , {
 "Length" , "gsm_a.len" , FT_UINT16 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_element_value , {
 "Element Value" , "gsm_a.element_value" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_extension , {
 "Extension" , "gsm_a.extension" , FT_BOOLEAN , 8 , TFS ( & gsm_a_extension_value ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_L3_protocol_discriminator , {
 "Protocol discriminator" , "gsm_a.L3_protocol_discriminator" , FT_UINT8 , BASE_HEX , VALS ( protocol_discriminator_vals ) , 0x0f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_call_prio , {
 "Call priority" , "gsm_a.call_prio" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_call_prio_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_type_of_ciph_alg , {
 "Call priority" , "gsm_a.call_prio" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_gm_type_of_ciph_alg_vals ) , 0x07 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_att , {
 "ATT" , "gsm_a.att" , FT_BOOLEAN , 8 , TFS ( & gsm_a_att_value ) , 0x01 , "ttach-detach allowed" , HFILL }
 }
 , {
 & hf_gsm_a_nmo_1 , {
 "NMO I" , "gsm_a.nmo_1" , FT_BOOLEAN , 8 , TFS ( & gsm_a_nmo_1_value ) , 0x02 , "Network Mode of Operation I" , HFILL }
 }
 , {
 & hf_gsm_a_nmo , {
 "NMO" , "gsm_a.nmo" , FT_BOOLEAN , 8 , TFS ( & gsm_a_nmo_value ) , 0x01 , "Network Mode of Operation" , HFILL }
 }
 , {
 & hf_gsm_a_old_xid , {
 "Old XID" , "gsm_a.old_xid" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_pld_xid_vals ) , 0x10 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_iov_ui , {
 "IOV-UI" , "gsm_a.iov_ui" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ext_periodic_timers , {
 "Extended periodic timers" , "gsm_a.ext_periodic_timers" , FT_BOOLEAN , BASE_NONE , TFS ( & gsm_a_ext_periodic_timers_value ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_skip_ind , {
 "Skip Indicator" , "gsm_a.skip.ind" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_skip_ind_vals ) , 0xf0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_b7spare , {
 "Spare" , "gsm_a.spareb7" , FT_UINT8 , BASE_DEC , NULL , 0x40 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_b8spare , {
 "Spare" , "gsm_a.spareb8" , FT_UINT8 , BASE_DEC , NULL , 0x80 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_spare_bits , {
 "Spare bit(s)" , "gsm_a.spare_bits" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_multi_bnd_sup_fields , {
 "Multiband supported field" , "gsm_a.multi_bnd_sup_fields" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_pgsm_supported , {
 "P-GSM Supported" , "gsm_a.classmark3.pgsmSupported" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_egsm_supported , {
 "E-GSM or R-GSM Supported" , "gsm_a.classmark3.egsmSupported" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm1800_supported , {
 "GSM 1800 Supported" , "gsm_a.classmark3.gsm1800Supported" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ass_radio_cap1 , {
 "Associated Radio Capability 1" , "gsm_a.classmark3.ass_radio_cap1" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ass_radio_cap2 , {
 "Associated Radio Capability 2" , "gsm_a.classmark3.ass_radio_cap2" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_cm3_A5_bits , {
 "A5 bits" , "gsm_a.classmark3.a5_bits" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_rsupport , {
 "R Support" , "gsm_a.classmark3.rsupport" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_r_capabilities , {
 "R-GSM band Associated Radio Capability" , "gsm_a.classmark3.r_capabilities" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_multislot_capabilities , {
 "HSCSD Multi Slot Capability" , "gsm_a.classmark3.multislot_capabilities" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_multislot_class , {
 "HSCSD Multi Slot Class" , "gsm_a.classmark3.multislot_cap" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ucs2_treatment , {
 "UCS2 treatment" , "gsm_a.UCS2_treatment" , FT_BOOLEAN , BASE_NONE , TFS ( & UCS2_treatment_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_extended_measurement_cap , {
 "Extended Measurement Capability" , "gsm_a.classmark3.ext_meas_cap" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ms_measurement_capability , {
 "MS measurement capability" , "gsm_a.classmark3.ms_measurement_capability" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_sms_value , {
 "SMS_VALUE (Switch-Measure-Switch)" , "gsm_a.classmark3.sms_value" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_sms_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_sm_value , {
 "SM_VALUE (Switch-Measure)" , "gsm_a.classmark3.sm_value" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_sms_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ms_pos_method_cap_present , {
 "MS Positioning Method Capability present" , "gsm_a.classmark3.ms_pos_method_cap_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ms_pos_method , {
 "MS Positioning Method" , "gsm_a.classmark3.ms_pos_method" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ms_assisted_e_otd , {
 "MS assisted E-OTD" , "gsm_a.classmark3.ms_assisted_e_otd" , FT_BOOLEAN , BASE_NONE , TFS ( & ms_assisted_e_otd_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ms_based_e_otd , {
 "MS based E-OTD" , "gsm_a.classmark3.ms_based_e_otd" , FT_BOOLEAN , BASE_NONE , TFS ( & ms_based_e_otd_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ms_assisted_gps , {
 "MS assisted GPS" , "gsm_a.classmark3.ms_assisted_gps" , FT_BOOLEAN , BASE_NONE , TFS ( & ms_assisted_gps_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ms_based_gps , {
 "MS based GPS" , "gsm_a.classmark3.ms_based_gps" , FT_BOOLEAN , BASE_NONE , TFS ( & ms_based_gps_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ms_conventional_gps , {
 "MS Conventional GPS" , "gsm_a.classmark3.ms_conventional_gps" , FT_BOOLEAN , BASE_NONE , TFS ( & ms_conventional_gps_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ecsd_multi_slot_capability , {
 "ECSD Multi Slot Capability present" , "gsm_a.classmark3.ecsd_multi_slot_capability" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ecsd_multi_slot_class , {
 "ECSD Multi Slot Class" , "gsm_a.classmark3.ecsd_multi_slot_class" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_8_psk_struct_present , {
 "8-PSK Struct present" , "gsm_a.classmark3.8_psk_struct_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_8_psk_struct , {
 "8-PSK Struct" , "gsm_a.classmark3.8_psk_struct" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_modulation_capability , {
 "Modulation Capability" , "gsm_a.classmark3.modulation_capability" , FT_BOOLEAN , BASE_NONE , TFS ( & modulation_capability_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_8_psk_rf_power_capability_1_present , {
 "8-PSK RF Power Capability 1 present" , "gsm_a.classmark3.8_psk_rf_power_capability_1_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_8_psk_rf_power_capability_1 , {
 "8-PSK RF Power Capability 1" , "gsm_a.classmark3.8_psk_rf_power_capability_1" , FT_UINT8 , BASE_HEX , VALS ( eight_psk_rf_power_capability_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_8_psk_rf_power_capability_2_present , {
 "8-PSK RF Power Capability 2 present" , "gsm_a.classmark3.8_psk_rf_power_capability_2_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_8_psk_rf_power_capability_2 , {
 "8-PSK RF Power Capability 2" , "gsm_a.classmark3.8_psk_rf_power_capability_2" , FT_UINT8 , BASE_HEX , VALS ( eight_psk_rf_power_capability_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_400_band_info_present , {
 "GSM 400 Band Information present" , "gsm_a.classmark3.gsm_400_band_info_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_400_bands_supported , {
 "GSM 400 Bands Supported" , "gsm_a.classmark3.gsm_400_bands_supported" , FT_UINT8 , BASE_HEX , VALS ( gsm_400_bands_supported_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_400_assoc_radio_cap , {
 "GSM 400 Associated Radio Capability" , "gsm_a.classmark3.gsm_400_assoc_radio_cap" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_850_assoc_radio_cap_present , {
 "GSM 850 Associated Radio Capability present" , "gsm_a.classmark3.gsm_850_assoc_radio_cap_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_850_assoc_radio_cap , {
 "GSM 850 Associated Radio Capability" , "gsm_a.classmark3.gsm_850_assoc_radio_cap" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_1900_assoc_radio_cap_present , {
 "GSM 1900 Associated Radio Capability present" , "gsm_a.classmark3.gsm_1900_assoc_radio_cap_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_1900_assoc_radio_cap , {
 "GSM 1900 Associated Radio Capability" , "gsm_a.classmark3.gsm_1900_assoc_radio_cap" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_umts_fdd_rat_cap , {
 "UMTS FDD Radio Access Technology Capability" , "gsm_a.classmark3.umts_fdd_rat_cap" , FT_BOOLEAN , BASE_NONE , TFS ( & umts_fdd_rat_cap_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_umts_384_mcps_tdd_rat_cap , {
 "UMTS 3.84 Mcps TDD Radio Access Technology Capability" , "gsm_a.classmark3.umts_384_mcps_tdd_rat_cap" , FT_BOOLEAN , BASE_NONE , TFS ( & umts_384_mcps_tdd_rat_cap_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_cdma_2000_rat_cap , {
 "CDMA 2000 Radio Access Technology Capability" , "gsm_a.classmark3.cdma_2000_rat_cap" , FT_BOOLEAN , BASE_NONE , TFS ( & cdma_2000_rat_cap_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtm_e_gprs_multi_slot_info_present , {
 "DTM E/GPRS Multi Slot Information present" , "gsm_a.classmark3.dtm_e_gprs_multi_slot_info_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtm_gprs_multi_slot_class , {
 "DTM GPRS Multi Slot Class" , "gsm_a.classmark3.dtm_gprs_multi_slot_class" , FT_UINT8 , BASE_DEC , VALS ( dtm_gprs_multi_slot_class_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_single_slot_dtm , {
 "Single Slot DTM" , "gsm_a.classmark3.single_slot_dtm_supported" , FT_BOOLEAN , BASE_NONE , TFS ( & single_slot_dtm_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtm_egprs_multi_slot_class_present , {
 "DTM EGPRS Multi Slot Class present" , "gsm_a.classmark3.dtm_egprs_multi_slot_class_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtm_egprs_multi_slot_class , {
 "DTM EGPRS Multi Slot Class" , "gsm_a.classmark3.dtm_egprs_multi_slot_class" , FT_UINT8 , BASE_DEC , VALS ( dtm_gprs_multi_slot_class_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_single_band_support , {
 "Single Band Support" , "gsm_a.classmark3.single_band_support" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_band , {
 "GSM Band" , "gsm_a.classmark3.gsm_band" , FT_UINT8 , BASE_DEC , VALS ( gsm_band_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_750_assoc_radio_cap_present , {
 "GSM 750 Associated Radio Capability present" , "gsm_a.classmark3.gsm_750_assoc_radio_cap_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_750_assoc_radio_cap , {
 "GSM 750 Associated Radio Capability" , "gsm_a.classmark3.gsm_750_assoc_radio_cap" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_umts_128_mcps_tdd_rat_cap , {
 "UMTS 1.28 Mcps TDD Radio Access Technology Capability" , "gsm_a.classmark3.umts_128_mcps_tdd_rat_cap" , FT_BOOLEAN , BASE_NONE , TFS ( & umts_128_mcps_tdd_rat_cap_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geran_feature_package_1 , {
 "GERAN Feature Package 1" , "gsm_a.classmark3.geran_feature_package_1" , FT_BOOLEAN , BASE_NONE , TFS ( & geran_feature_package_1_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ext_dtm_e_gprs_multi_slot_info_present , {
 "Extended DTM E/GPRS Multi Slot Information present" , "gsm_a.classmark3.ext_dtm_e_gprs_info_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ext_dtm_gprs_multi_slot_class , {
 "Extended DTM GPRS Multi Slot Class" , "gsm_a.classmark3.ext_dtm_gprs_multi_slot_class" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ext_dtm_egprs_multi_slot_class , {
 "Extended DTM EGPRS Multi Slot Class" , "gsm_a.classmark3.ext_dtm_egprs_multi_slot_class" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_high_multislot_cap_present , {
 "High Multislot Capability present" , "gsm_a.classmark3.high_multislot_cap_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_high_multislot_cap , {
 "High Multislot Capability" , "gsm_a.classmark3.high_multislot_cap" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geran_iu_mode_support , {
 "GERAN Iu Mode Support" , "gsm_a.classmark3.geran_iu_mode_support" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geran_iu_mode_cap , {
 "GERAN Iu Mode Capabilities" , "gsm_a.classmark3.geran_iu_mode_cap" , FT_UINT24 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geran_iu_mode_cap_length , {
 "Length" , "gsm_a.classmark3.geran_iu_mode_cap.length" , FT_UINT8 , BASE_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_flo_iu_cap , {
 "FLO Iu Capability" , "gsm_a.classmark3.geran_iu_mode_cap.flo_iu_cap" , FT_BOOLEAN , BASE_NONE , TFS ( & flo_iu_cap_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geran_feature_package_2 , {
 "GERAN Feature Package 2" , "gsm_a.classmark3.geran_feature_package_2" , FT_BOOLEAN , BASE_NONE , TFS ( & geran_feature_package_2_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gmsk_multislot_power_prof , {
 "GMSK Multislot Power Profile" , "gsm_a.classmark3.gmsk_multislot_power_prof" , FT_UINT8 , BASE_DEC , VALS ( gmsk_multislot_power_prof_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_8_psk_multislot_power_prof , {
 "8-PSK Multislot Power Profile" , "gsm_a.classmark3.8_psk_multislot_power_prof" , FT_UINT8 , BASE_DEC , VALS ( eight_psk_multislot_power_prof_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_t_gsm_400_band_info_present , {
 "T-GSM 400 Band Information present" , "gsm_a.classmark3.gsm_400_band_info_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_t_gsm_400_bands_supported , {
 "T-GSM 400 Bands Supported" , "gsm_a.classmark3.t_gsm_400_bands_supported" , FT_UINT8 , BASE_HEX , VALS ( t_gsm_400_bands_supported_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_t_gsm_400_assoc_radio_cap , {
 "T-GSM 400 Associated Radio Capability" , "gsm_a.classmark3.t_gsm_400_assoc_radio_cap" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_t_gsm_900_assoc_radio_cap_present , {
 "T-GSM 900 Associated Radio Capability present" , "gsm_a.classmark3.t_gsm_900_assoc_radio_cap_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_t_gsm_900_assoc_radio_cap , {
 "T-GSM 900 Associated Radio Capability" , "gsm_a.classmark3.t_gsm_900_assoc_radio_cap" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_downlink_adv_receiver_perf , {
 "Downlink Advanced Receiver Performance" , "gsm_a.classmark3.downlink_adv_receiver_perf" , FT_UINT8 , BASE_DEC , VALS ( downlink_adv_receiver_perf_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtm_enhancements_cap , {
 "DTM Enhancements Capability" , "gsm_a.classmark3.dtm_enhancements_capability" , FT_BOOLEAN , BASE_NONE , TFS ( & dtm_enhancements_cap_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtm_e_gprs_high_multi_slot_info_present , {
 "DTM E/GPRS High Multi Slot Information present" , "gsm_a.classmark3.dtm_e_gprs_high_mutli_slot_info_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtm_gprs_high_multi_slot_class , {
 "DTM GPRS Multi Slot Class" , "gsm_a.classmark3.dtm_gprs_multi_slot_class" , FT_UINT8 , BASE_DEC , VALS ( dtm_gprs_high_multi_slot_class_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_offset_required , {
 "Offset required" , "gsm_a.classmark3.offset_required" , FT_BOOLEAN , BASE_NONE , TFS ( & offset_required_vals ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtm_egprs_high_multi_slot_class_present , {
 "DTM EGPRS High Multi Slot Class present" , "gsm_a.classmark3.dtm_egprs_high_multi_slot_class_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_dtm_egprs_high_multi_slot_class , {
 "DTM EGPRS High Multi Slot Class" , "gsm_a.classmark3.dtm_egprs_high_multi_slot_class" , FT_UINT8 , BASE_DEC , VALS ( dtm_gprs_high_multi_slot_class_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_repeated_acch_cap , {
 "Repeated ACCH Capability" , "gsm_a.classmark3.repeated_acch_cap" , FT_BOOLEAN , BASE_NONE , TFS ( & repeated_acch_cap_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_710_assoc_radio_cap_present , {
 "GSM 710 Associated Radio Capability present" , "gsm_a.classmark3.gsm_710_assoc_radio_cap_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_gsm_710_assoc_radio_cap , {
 "GSM 710 Associated Radio Capability" , "gsm_a.classmark3.gsm_710_assoc_radio_cap" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_t_gsm_810_assoc_radio_cap_present , {
 "T-GSM 810 Associated Radio Capability present" , "gsm_a.classmark3.t_gsm_810_assoc_radio_cap_present" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_t_gsm_810_assoc_radio_cap , {
 "T-GSM 810 Associated Radio Capability" , "gsm_a.classmark3.t_gsm_810_assoc_radio_cap" , FT_UINT8 , BASE_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ciphering_mode_setting_cap , {
 "Ciphering Mode Setting Capability" , "gsm_a.classmark3.ciphering_mode_setting_cap" , FT_BOOLEAN , BASE_NONE , TFS ( & ciphering_mode_setting_cap_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_additional_positioning_caps , {
 "Additional Positioning Capabilities" , "gsm_a.classmark3.additional_positioning_caps" , FT_BOOLEAN , BASE_NONE , TFS ( & additional_positioning_caps_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_e_utra_fdd_support , {
 "E-UTRA FDD support" , "gsm_a.classmark3.e_utra_fdd_support" , FT_BOOLEAN , BASE_NONE , TFS ( & e_utra_fdd_support_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_e_utra_tdd_support , {
 "E-UTRA TDD support" , "gsm_a.classmark3.e_utra_tdd_support" , FT_BOOLEAN , BASE_NONE , TFS ( & e_utra_tdd_support_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_e_utra_meas_and_report_support , {
 "E-UTRA Measurement and Reporting support" , "gsm_a.classmark3.e_utra_meas_and_report_support" , FT_BOOLEAN , BASE_NONE , TFS ( & e_utra_meas_and_report_support_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_prio_based_resel_support , {
 "Priority-based reselection support" , "gsm_a.classmark3.prio_based_resel_support" , FT_BOOLEAN , BASE_NONE , TFS ( & prio_based_resel_support_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_utra_csg_cells_reporting , {
 "UTRA CSG Cells Reporting" , "gsm_a.classmark3.utra_csg_cells_reporting" , FT_BOOLEAN , BASE_NONE , TFS ( & utra_csg_cells_reporting_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_vamos_level , {
 "VAMOS Level" , "gsm_a.classmark3.vamos_level" , FT_UINT8 , BASE_DEC , VALS ( vamos_level_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_tighter_cap , {
 "TIGHTER Capability" , "gsm_a.classmark3.tighter_cap" , FT_UINT8 , BASE_DEC , VALS ( tighter_cap_level_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_selective_ciph_down_sacch , {
 "Selective Ciphering of Downlink SACCH" , "gsm_a.classmark3.selective_ciph_down_sacch" , FT_BOOLEAN , BASE_NONE , TFS ( & tfs_supported_not_supported ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_cs_to_ps_srvcc_geran_to_utra , {
 "CS to PS SRVCC from GERAN to UTRA" , "gsm_a.classmark3.cs_to_ps_srvcc_geran_to_utra" , FT_UINT8 , BASE_DEC , VALS ( cs_to_ps_srvcc_geran_to_utra_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_cs_to_ps_srvcc_geran_to_eutra , {
 "CS to PS SRVCC from GERAN to E-UTRA" , "gsm_a.classmark3.cs_to_ps_srvcc_geran_to_eutra" , FT_UINT8 , BASE_DEC , VALS ( cs_to_ps_srvcc_geran_to_eutra_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geran_network_sharing_support , {
 "GERAN Network Sharing support" , "gsm_a.classmark3.geran_network_sharing_support" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_eutra_wb_rsrq_support , {
 "E-UTRA Wideband RSRQ measurements support" , "gsm_a.classmark3.eutra_wb_rsrq_support" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_er_band_support , {
 "ER Band support" , "gsm_a.classmark3.er_band_support" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_utra_mfbi_support , {
 "UTRA Multiple Frequency Band Indicators support" , "gsm_a.classmark3.utra_mfbi_support" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_eutra_mfbi_support , {
 "E-UTRA Multiple Frequency Band Indicators support" , "gsm_a.classmark3.eutra_mfbi_support" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ext_tsc_set_cap_support , {
 "Extended TSC Set Capability support" , "gsm_a.classmark3.ext_tsc_set_cap_support" , FT_BOOLEAN , BASE_NONE , TFS ( & true_false_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ext_earfcn_value_range , {
 "Extended EARFCN value range" , "gsm_a.classmark3.ext_earfcn_value_range" , FT_BOOLEAN , BASE_NONE , TFS ( & tfs_supported_not_supported ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_type_of_shape , {
 "Location estimate" , "gsm_a.gad.location_estimate" , FT_UINT8 , BASE_DEC , VALS ( type_of_shape_vals ) , 0xf0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_sign_of_lat , {
 "Sign of latitude" , "gsm_a.gad.sign_of_latitude" , FT_UINT8 , BASE_DEC , VALS ( sign_of_latitude_vals ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_deg_of_lat , {
 "Degrees of latitude" , "gsm_a.gad.deg_of_latitude" , FT_UINT24 , BASE_DEC , NULL , 0x7fffff , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_deg_of_long , {
 "Degrees of longitude" , "gsm_a.gad.deg_of_longitude" , FT_INT24 , BASE_DEC , NULL , 0xffffff , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_uncertainty_code , {
 "Uncertainty code" , "gsm_a.gad.uncertainty_code" , FT_UINT8 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_uncertainty_semi_major , {
 "Uncertainty semi-major" , "gsm_a.gad.uncertainty_semi_major" , FT_UINT8 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_uncertainty_semi_minor , {
 "Uncertainty semi-minor" , "gsm_a.gad.uncertainty_semi_minor" , FT_UINT8 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_orientation_of_major_axis , {
 "Orientation of major axis" , "gsm_a.gad.orientation_of_major_axis" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_uncertainty_altitude , {
 "Uncertainty Altitude" , "gsm_a.gad.uncertainty_altitude" , FT_UINT8 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_confidence , {
 "Confidence(%)" , "gsm_a.gad.confidence" , FT_UINT8 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_no_of_points , {
 "Number of points" , "gsm_a.gad.no_of_points" , FT_UINT8 , BASE_DEC , NULL , 0x0f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_velocity_type , {
 "Number of points" , "gsm_a.gad.velocity_type" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_velocity_type_vals ) , 0xf0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_bearing , {
 "Bearing" , "gsm_a.gad.bearing" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_horizontal_speed , {
 "Horizontal Speed" , "gsm_a.gad.horizontal_velocity" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_vertical_speed , {
 "Vertical Speed" , "gsm_a.gad.vertical_speed" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_uncertainty_speed , {
 "Uncertainty Speed" , "gsm_a.gad.uncertainty_speed" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_h_uncertainty_speed , {
 "Horizontal Uncertainty Speed" , "gsm_a.gad.v_uncertainty_speed" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_v_uncertainty_speed , {
 "Vertical Uncertainty Speed" , "gsm_a.gad.h_uncertainty_speed" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_d , {
 "Direction of Vertical Speed" , "gsm_a.gad.d" , FT_BOOLEAN , 8 , TFS ( & gsm_a_dir_of_ver_speed_vals ) , 0x08 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_D , {
 "D: Direction of Altitude" , "gsm_a.gad.D" , FT_UINT16 , BASE_DEC , VALS ( dir_of_alt_vals ) , 0x8000 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_altitude , {
 "Altitude in meters" , "gsm_a.gad.altitude" , FT_UINT16 , BASE_DEC , NULL , 0x7fff , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_inner_radius , {
 "Inner radius" , "gsm_a.gad.altitude" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_uncertainty_radius , {
 "Uncertainty radius" , "gsm_a.gad.no_of_points" , FT_UINT8 , BASE_DEC , NULL , 0x7f , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_offset_angle , {
 "Offset angle" , "gsm_a.gad.offset_angle" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_geo_loc_included_angle , {
 "Included angle" , "gsm_a.gad.included_angle" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_key_seq , {
 "key sequence" , "gsm_a.key_seq" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_key_seq_vals ) , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_lac , {
 "Location Area Code (LAC)" , "gsm_a.lac" , FT_UINT16 , BASE_HEX_DEC , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_spare_nibble , {
 "Spare Nibble" , "gsm_a.spare" , FT_UINT8 , BASE_DEC_HEX , NULL , 0x00 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_filler , {
 "Filler" , "gsm_a.filler" , FT_UINT8 , BASE_HEX , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_identity_digit1 , {
 "Identity Digit 1" , "gsm_a.identity_digit1" , FT_UINT8 , BASE_HEX , NULL , 0xF0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_group_call_reference , {
 "Group or Broadcast call reference" , "gsm_a.group_call_reference" , FT_UINT32 , BASE_DEC_HEX , NULL , 0xffffffe0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_service_flag , {
 "SF Service Flag" , "gsm_a.service_flag" , FT_BOOLEAN , 32 , TFS ( & tfs_vgcs_vbs ) , 0x00000010 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_af_acknowledgement , {
 "AF Acknowledgement" , "gsm_a.af_acknowledgement" , FT_BOOLEAN , 32 , TFS ( & tfs_required_not_required ) , 0x00000008 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_call_priority , {
 "Call Priority" , "gsm_a.call_priority" , FT_UINT32 , BASE_DEC , VALS ( gsm_a_call_priority_vals ) , 0x00000007 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_ciphering_info , {
 "Ciphering Information" , "gsm_a.ciphering_info" , FT_UINT8 , BASE_HEX , NULL , 0xf0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_sapi , {
 "SAPI (Service Access Point Identifier)" , "gsm_a.sapi" , FT_UINT8 , BASE_DEC , VALS ( gsm_a_sapi_vals ) , 0x30 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_mobile_country_code , {
 "Mobile Country Code (MCC)" , "gsm_a.mobile_country_code" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_gsm_a_mobile_network_code , {
 "Mobile Network Code (MNC)" , "gsm_a.mobile_network_code" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , }
 ;

 static ei_register_info ei [ ] = {
 {
 & ei_gsm_a_extraneous_data , {
 "gsm_a.extraneous_data" , PI_PROTOCOL , PI_NOTE , "Extraneous Data, dissector bug or later version spec(report to wireshark.org)" , EXPFILL }
 }
 , {
 & ei_gsm_a_unknown_element , {
 "gsm_a.unknown_element" , PI_PROTOCOL , PI_ERROR , "Unknown - aborting dissection" , EXPFILL }
 }
 , {
 & ei_gsm_a_unknown_pdu_type , {
 "gsm_a.unknown_pdu_type" , PI_PROTOCOL , PI_WARN , "Unknown PDU type" , EXPFILL }
 }
 , {
 & ei_gsm_a_no_element_dissector , {
 "gsm_a.no_element_dissector" , PI_PROTOCOL , PI_WARN , "No element dissector, rest of dissection may be incorrect" , EXPFILL }
 }
 , {
 & ei_gsm_a_format_not_supported , {
 "gsm_a.format_not_supported" , PI_PROTOCOL , PI_WARN , "Format not supported" , EXPFILL }
 }
 , {
 & ei_gsm_a_mobile_identity_type , {
 "gsm_a.ie.mobileid.type.unknown" , PI_PROTOCOL , PI_WARN , "Format unknown" , EXPFILL }
 }
 , }
 ;
 expert_module_t * expert_a_common ;
 static tap_param gsm_a_stat_params [ ] = {
 {
 PARAM_FILTER , "filter" , "Filter" , NULL , TRUE }
 }
 ;
 static new_stat_tap_ui gsm_a_bssmap_stat_table = {
 REGISTER_STAT_GROUP_TELEPHONY_GSM , "A-Interface BSSMAP" , "gsm_a" , "gsm_a,bssmap" , gsm_a_bssmap_stat_init , gsm_a_bssmap_stat_packet , gsm_a_stat_reset , gsm_a_stat_free_table_item , NULL , sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) , gsm_a_stat_fields , sizeof ( gsm_a_stat_params ) / sizeof ( tap_param ) , gsm_a_stat_params , NULL }
 ;
 static new_stat_tap_ui gsm_a_dtap_mm_stat_table = {
 REGISTER_STAT_GROUP_TELEPHONY_GSM , "A-Interface DTAP Mobility Management" , "gsm_a" , "gsm_a,dtap_mm" , gsm_a_dtap_mm_stat_init , gsm_a_dtap_mm_stat_packet , gsm_a_stat_reset , NULL , NULL , sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) , gsm_a_stat_fields , sizeof ( gsm_a_stat_params ) / sizeof ( tap_param ) , gsm_a_stat_params , NULL }
 ;
 static new_stat_tap_ui gsm_a_dtap_rr_stat_table = {
 REGISTER_STAT_GROUP_TELEPHONY_GSM , "A-Interface DTAP Radio Resource Management" , "gsm_a" , "gsm_a,dtap_rr" , gsm_a_dtap_rr_stat_init , gsm_a_dtap_rr_stat_packet , gsm_a_stat_reset , NULL , NULL , sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) , gsm_a_stat_fields , sizeof ( gsm_a_stat_params ) / sizeof ( tap_param ) , gsm_a_stat_params , NULL }
 ;
 static new_stat_tap_ui gsm_a_dtap_cc_stat_table = {
 REGISTER_STAT_GROUP_TELEPHONY_GSM , "A-Interface DTAP Call Control" , "gsm_a" , "gsm_a,dtap_cc" , gsm_a_dtap_cc_stat_init , gsm_a_dtap_cc_stat_packet , gsm_a_stat_reset , NULL , NULL , sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) , gsm_a_stat_fields , sizeof ( gsm_a_stat_params ) / sizeof ( tap_param ) , gsm_a_stat_params , NULL }
 ;
 static new_stat_tap_ui gsm_a_dtap_gmm_stat_table = {
 REGISTER_STAT_GROUP_TELEPHONY_GSM , "A-Interface DTAP GPRS Mobility Management" , "gsm_a" , "gsm_a,dtap_gmm" , gsm_a_dtap_gmm_stat_init , gsm_a_dtap_gmm_stat_packet , gsm_a_stat_reset , NULL , NULL , sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) , gsm_a_stat_fields , sizeof ( gsm_a_stat_params ) / sizeof ( tap_param ) , gsm_a_stat_params , NULL }
 ;
 static new_stat_tap_ui gsm_a_dtap_sm_stat_table = {
 REGISTER_STAT_GROUP_TELEPHONY_GSM , "A-Interface DTAP GPRS Session Management" , "gsm_a" , "gsm_a,dtap_sm" , gsm_a_dtap_sm_stat_init , gsm_a_dtap_sm_stat_packet , gsm_a_stat_reset , NULL , NULL , sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) , gsm_a_stat_fields , sizeof ( gsm_a_stat_params ) / sizeof ( tap_param ) , gsm_a_stat_params , NULL }
 ;
 static new_stat_tap_ui gsm_a_dtap_sms_stat_table = {
 REGISTER_STAT_GROUP_TELEPHONY_GSM , "A-Interface DTAP Short Message Service" , "gsm_a" , "gsm_a,dtap_sms" , gsm_a_dtap_sms_stat_init , gsm_a_dtap_sms_stat_packet , gsm_a_stat_reset , NULL , NULL , sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) , gsm_a_stat_fields , sizeof ( gsm_a_stat_params ) / sizeof ( tap_param ) , gsm_a_stat_params , NULL }
 ;
 static new_stat_tap_ui gsm_a_dtap_tp_stat_table = {
 REGISTER_STAT_GROUP_TELEPHONY_GSM , "A-Interface DTAP Special Conformance Testing Functions" , "gsm_a" , "gsm_a,dtap_tp" , gsm_a_dtap_tp_stat_init , gsm_a_dtap_tp_stat_packet , gsm_a_stat_reset , NULL , NULL , sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) , gsm_a_stat_fields , sizeof ( gsm_a_stat_params ) / sizeof ( tap_param ) , gsm_a_stat_params , NULL }
 ;
 static new_stat_tap_ui gsm_a_dtap_ss_stat_table = {
 REGISTER_STAT_GROUP_TELEPHONY_GSM , "A-Interface DTAP Supplementary Services" , "gsm_a" , "gsm_a,dtap_ss" , gsm_a_dtap_ss_stat_init , gsm_a_dtap_ss_stat_packet , gsm_a_stat_reset , NULL , NULL , sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) , gsm_a_stat_fields , sizeof ( gsm_a_stat_params ) / sizeof ( tap_param ) , gsm_a_stat_params , NULL }
 ;
 static new_stat_tap_ui gsm_a_sacch_rr_stat_table = {
 REGISTER_STAT_GROUP_TELEPHONY_GSM , "A-Interface SACCH" , "gsm_a" , "gsm_a,dtap_sacch" , gsm_a_sacch_rr_stat_init , gsm_a_sacch_rr_stat_packet , gsm_a_stat_reset , NULL , NULL , sizeof ( gsm_a_stat_fields ) / sizeof ( stat_tap_table_item ) , gsm_a_stat_fields , sizeof ( gsm_a_stat_params ) / sizeof ( tap_param ) , gsm_a_stat_params , NULL }
 ;
 last_offset = NUM_INDIVIDUAL_ELEMS ;
 ett [ 0 ] = & ett_gsm_a_plmn ;
 for ( i = 0 ;
 i < NUM_GSM_COMMON_ELEM ;
 i ++ , last_offset ++ ) {
 ett_gsm_common_elem [ i ] = - 1 ;
 ett [ last_offset ] = & ett_gsm_common_elem [ i ] ;
 }
 proto_a_common = proto_register_protocol ( "GSM A-I/F COMMON" , "GSM COMMON" , "gsm_a" ) ;
 proto_register_field_array ( proto_a_common , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 expert_a_common = expert_register_protocol ( proto_a_common ) ;
 expert_register_field_array ( expert_a_common , ei , array_length ( ei ) ) ;
 gsm_a_tap = register_tap ( "gsm_a" ) ;
 register_new_stat_tap_ui ( & gsm_a_bssmap_stat_table ) ;
 register_new_stat_tap_ui ( & gsm_a_dtap_mm_stat_table ) ;
 register_new_stat_tap_ui ( & gsm_a_dtap_rr_stat_table ) ;
 register_new_stat_tap_ui ( & gsm_a_dtap_cc_stat_table ) ;
 register_new_stat_tap_ui ( & gsm_a_dtap_gmm_stat_table ) ;
 register_new_stat_tap_ui ( & gsm_a_dtap_sms_stat_table ) ;
 register_new_stat_tap_ui ( & gsm_a_dtap_sm_stat_table ) ;
 register_new_stat_tap_ui ( & gsm_a_dtap_ss_stat_table ) ;
 register_new_stat_tap_ui ( & gsm_a_dtap_tp_stat_table ) ;
 register_new_stat_tap_ui ( & gsm_a_sacch_rr_stat_table ) ;
 }