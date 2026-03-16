guint16 de_ms_cm_3 ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guint32 bit_offset ;
 guint8 length ;
 proto_tree * subtree ;
 proto_item * item ;
 guint32 bits_left , target_bit_offset , old_bit_offset ;
 guint64 multi_bnd_sup_fields , rsupport , multislotCapability ;
 guint64 msMeasurementCapability , msPosMethodCapPresent ;
 guint64 ecsdMultiSlotCapability , eightPskStructPresent , eightPskStructRfPowerCapPresent ;
 guint64 gsm400BandInfoPresent , gsm850AssocRadioCapabilityPresent ;
 guint64 gsm1900AssocRadioCapabilityPresent , dtmEGprsMultiSlotInfoPresent ;
 guint64 dtmEgprsMultiSlotClassPresent , singleBandSupport ;
 guint64 gsm750AssocRadioCapabilityPresent , extDtmEGprsMultiSlotInfoPresent ;
 guint64 highMultislotCapPresent , geranIuModeSupport ;
 guint64 tGsm400BandInfoPresent , tGsm900AssocRadioCapabilityPresent , dtmEGprsHighMultiSlotInfoPresent ;
 guint64 dtmEgprsHighMultiSlotClassPresent , gsm710AssocRadioCapabilityPresent ;
 guint64 tGsm810AssocRadioCapabilityPresent ;
 curr_offset = offset ;
 bit_offset = curr_offset << 3 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 item = proto_tree_add_bits_ret_val ( tree , hf_gsm_a_multi_bnd_sup_fields , tvb , bit_offset , 3 , & multi_bnd_sup_fields , ENC_BIG_ENDIAN ) ;
 subtree = proto_item_add_subtree ( item , ett_gsm_common_elem [ DE_MS_CM_3 ] ) ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_gsm1800_supported , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_egsm_supported , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_pgsm_supported , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 item = proto_tree_add_bits_item ( tree , hf_gsm_a_cm3_A5_bits , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 subtree = proto_item_add_subtree ( item , ett_gsm_common_elem [ DE_MS_CM_3 ] ) ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_A5_7_algorithm_sup , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_A5_6_algorithm_sup , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_A5_5_algorithm_sup , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_A5_4_algorithm_sup , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 switch ( multi_bnd_sup_fields ) {
 case 0 : break ;
 case 1 : case 2 : case 4 : proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset += 4 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_ass_radio_cap1 , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset += 4 ;
 break ;
 case 5 : case 6 : proto_tree_add_bits_item ( tree , hf_gsm_a_ass_radio_cap2 , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset += 4 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_ass_radio_cap1 , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset += 4 ;
 break ;
 default : break ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_rsupport , tvb , bit_offset , 1 , & rsupport , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 if ( rsupport == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_r_capabilities , tvb , bit_offset , 3 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 3 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_multislot_capabilities , tvb , bit_offset , 1 , & multislotCapability , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 if ( multislotCapability == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_multislot_class , tvb , bit_offset , 5 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 5 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_ucs2_treatment , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_extended_measurement_cap , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_ms_measurement_capability , tvb , bit_offset , 1 , & msMeasurementCapability , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( msMeasurementCapability == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_sms_value , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_sm_value , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_ms_pos_method_cap_present , tvb , bit_offset , 1 , & msPosMethodCapPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( msPosMethodCapPresent == 1 ) {
 item = proto_tree_add_bits_item ( tree , hf_gsm_a_ms_pos_method , tvb , bit_offset , 5 , ENC_BIG_ENDIAN ) ;
 subtree = proto_item_add_subtree ( item , ett_gsm_common_elem [ DE_MS_CM_3 ] ) ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_ms_assisted_e_otd , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_ms_based_e_otd , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_ms_assisted_gps , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_ms_based_gps , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_ms_conventional_gps , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset ++ ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_ecsd_multi_slot_capability , tvb , bit_offset , 1 , & ecsdMultiSlotCapability , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( ecsdMultiSlotCapability == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_ecsd_multi_slot_class , tvb , bit_offset , 5 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 5 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_8_psk_struct_present , tvb , bit_offset , 1 , & eightPskStructPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( eightPskStructPresent == 1 ) {
 guint8 psk_struct_len = 3 ;
 guint32 tmp_bit_offset = bit_offset ;
 tmp_bit_offset ++ ;
 if ( tvb_get_bits8 ( tvb , tmp_bit_offset , 1 ) == 1 ) {
 psk_struct_len += 2 ;
 tmp_bit_offset += 2 ;
 }
 tmp_bit_offset ++ ;
 if ( tvb_get_bits8 ( tvb , tmp_bit_offset , 1 ) == 1 ) {
 psk_struct_len += 2 ;
 }
 item = proto_tree_add_bits_item ( tree , hf_gsm_a_8_psk_struct , tvb , bit_offset , psk_struct_len , ENC_BIG_ENDIAN ) ;
 subtree = proto_item_add_subtree ( item , ett_gsm_common_elem [ DE_MS_CM_3 ] ) ;
 old_bit_offset = bit_offset ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_modulation_capability , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 proto_tree_add_bits_ret_val ( subtree , hf_gsm_a_8_psk_rf_power_capability_1_present , tvb , bit_offset , 1 , & eightPskStructRfPowerCapPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( eightPskStructRfPowerCapPresent == 1 ) {
 proto_tree_add_bits_item ( subtree , hf_gsm_a_8_psk_rf_power_capability_1 , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 }
 proto_tree_add_bits_ret_val ( subtree , hf_gsm_a_8_psk_rf_power_capability_2_present , tvb , bit_offset , 1 , & eightPskStructRfPowerCapPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( eightPskStructRfPowerCapPresent == 1 ) {
 proto_tree_add_bits_item ( subtree , hf_gsm_a_8_psk_rf_power_capability_2 , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 }
 length = ( guint8 ) ( ( bit_offset - old_bit_offset ) >> 3 ) ;
 if ( ( bit_offset - old_bit_offset ) & 0x07 ) length ++ ;
 proto_item_set_len ( item , length ) ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_gsm_400_band_info_present , tvb , bit_offset , 1 , & gsm400BandInfoPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( gsm400BandInfoPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_gsm_400_bands_supported , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_gsm_400_assoc_radio_cap , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_gsm_850_assoc_radio_cap_present , tvb , bit_offset , 1 , & gsm850AssocRadioCapabilityPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( gsm850AssocRadioCapabilityPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_gsm_850_assoc_radio_cap , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_gsm_1900_assoc_radio_cap_present , tvb , bit_offset , 1 , & gsm1900AssocRadioCapabilityPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( gsm1900AssocRadioCapabilityPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_gsm_1900_assoc_radio_cap , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_umts_fdd_rat_cap , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_umts_384_mcps_tdd_rat_cap , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_cdma_2000_rat_cap , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_dtm_e_gprs_multi_slot_info_present , tvb , bit_offset , 1 , & dtmEGprsMultiSlotInfoPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( dtmEGprsMultiSlotInfoPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtm_gprs_multi_slot_class , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_single_slot_dtm , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_dtm_egprs_multi_slot_class_present , tvb , bit_offset , 1 , & dtmEgprsMultiSlotClassPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( dtmEgprsMultiSlotClassPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtm_egprs_multi_slot_class , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 }
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_single_band_support , tvb , bit_offset , 1 , & singleBandSupport , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( singleBandSupport == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_gsm_band , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_gsm_750_assoc_radio_cap_present , tvb , bit_offset , 1 , & gsm750AssocRadioCapabilityPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( gsm750AssocRadioCapabilityPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_gsm_750_assoc_radio_cap , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_umts_128_mcps_tdd_rat_cap , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_geran_feature_package_1 , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_ext_dtm_e_gprs_multi_slot_info_present , tvb , bit_offset , 1 , & extDtmEGprsMultiSlotInfoPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( extDtmEGprsMultiSlotInfoPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_ext_dtm_gprs_multi_slot_class , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_ext_dtm_egprs_multi_slot_class , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_high_multislot_cap_present , tvb , bit_offset , 1 , & highMultislotCapPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( highMultislotCapPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_high_multislot_cap , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_geran_iu_mode_support , tvb , bit_offset , 1 , & geranIuModeSupport , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( geranIuModeSupport == 1 ) {
 length = tvb_get_bits8 ( tvb , bit_offset , 4 ) ;
 item = proto_tree_add_bits_item ( tree , hf_gsm_a_geran_iu_mode_cap , tvb , bit_offset , length + 4 , ENC_BIG_ENDIAN ) ;
 subtree = proto_item_add_subtree ( item , ett_gsm_common_elem [ DE_MS_CM_3 ] ) ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_geran_iu_mode_cap_length , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset += 4 ;
 target_bit_offset = bit_offset + length ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_flo_iu_cap , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset += 1 ;
 if ( target_bit_offset > bit_offset ) {
 proto_tree_add_bits_item ( subtree , hf_gsm_a_spare_bits , tvb , bit_offset , target_bit_offset - bit_offset , ENC_BIG_ENDIAN ) ;
 bit_offset = target_bit_offset ;
 }
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_geran_feature_package_2 , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 2 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_gmsk_multislot_power_prof , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 AVAILABLE_BITS_CHECK ( 2 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_8_psk_multislot_power_prof , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_t_gsm_400_band_info_present , tvb , bit_offset , 1 , & tGsm400BandInfoPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( tGsm400BandInfoPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_t_gsm_400_bands_supported , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_t_gsm_400_assoc_radio_cap , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_t_gsm_900_assoc_radio_cap_present , tvb , bit_offset , 1 , & tGsm900AssocRadioCapabilityPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( tGsm900AssocRadioCapabilityPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_t_gsm_900_assoc_radio_cap , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 }
 AVAILABLE_BITS_CHECK ( 2 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_downlink_adv_receiver_perf , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtm_enhancements_cap , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_dtm_e_gprs_high_multi_slot_info_present , tvb , bit_offset , 1 , & dtmEGprsHighMultiSlotInfoPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( dtmEGprsHighMultiSlotInfoPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtm_gprs_high_multi_slot_class , tvb , bit_offset , 3 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 3 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_offset_required , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_dtm_egprs_high_multi_slot_class_present , tvb , bit_offset , 1 , & dtmEgprsHighMultiSlotClassPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( dtmEgprsHighMultiSlotClassPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtm_egprs_high_multi_slot_class , tvb , bit_offset , 3 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 3 ;
 }
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_repeated_acch_cap , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_gsm_710_assoc_radio_cap_present , tvb , bit_offset , 1 , & gsm710AssocRadioCapabilityPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( gsm710AssocRadioCapabilityPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_gsm_710_assoc_radio_cap , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_ret_val ( tree , hf_gsm_a_t_gsm_810_assoc_radio_cap_present , tvb , bit_offset , 1 , & tGsm810AssocRadioCapabilityPresent , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 if ( tGsm810AssocRadioCapabilityPresent == 1 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_t_gsm_810_assoc_radio_cap , tvb , bit_offset , 4 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 4 ;
 }
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_ciphering_mode_setting_cap , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_additional_positioning_caps , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_e_utra_fdd_support , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_e_utra_tdd_support , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_e_utra_meas_and_report_support , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_prio_based_resel_support , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_utra_csg_cells_reporting , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 2 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_vamos_level , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 AVAILABLE_BITS_CHECK ( 2 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_tighter_cap , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_selective_ciph_down_sacch , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 2 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_cs_to_ps_srvcc_geran_to_utra , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 AVAILABLE_BITS_CHECK ( 2 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_cs_to_ps_srvcc_geran_to_eutra , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 2 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_geran_network_sharing_support , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_eutra_wb_rsrq_support , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_er_band_support , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_utra_mfbi_support , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_eutra_mfbi_support , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_ext_tsc_set_cap_support , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 AVAILABLE_BITS_CHECK ( 1 ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_ext_earfcn_value_range , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 bit_offset = bit_offset + 1 ;
 bits_left = ( ( ( len + offset ) << 3 ) - bit_offset ) & 0x07 ;
 if ( bits_left != 0 ) {
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , bit_offset , bits_left , ENC_BIG_ENDIAN ) ;
 bit_offset += bits_left ;
 }
 curr_offset = bit_offset >> 3 ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_extraneous_data ) ;
 return len ;
 }