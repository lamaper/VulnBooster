guint16 de_bearer_cap ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string , int string_len ) {
 guint8 oct ;
 guint8 itc ;
 gboolean extended ;
 guint32 curr_offset ;
 guint32 saved_offset ;
 proto_tree * subtree ;
 proto_item * item ;
 const gchar * str ;

 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_3 , NULL , "Octet 3" ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 itc = oct & 0x07 ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 switch ( is_uplink ) {
 case IS_UPLINK_FALSE : str = "Spare" ;
 break ;
 case IS_UPLINK_TRUE : switch ( itc ) {
 case DE_BC_ITC_SPEECH : if ( extended ) {
 switch ( ( oct & 0x60 ) >> 5 ) {
 case 1 : str = "MS supports at least full rate speech version 1 but does not support half rate speech version 1" ;
 break ;
 case 2 : str = "MS supports at least full rate speech version 1 and half rate speech version 1. MS has a greater preference for half rate speech version 1 than for full rate speech version 1" ;
 break ;
 case 3 : str = "MS supports at least full rate speech version 1 and half rate speech version 1. MS has a greater preference for full rate speech version 1 than for half rate speech version 1" ;
 break ;
 default : str = "Reserved" ;
 break ;
 }
 }
 else {
 switch ( ( oct & 0x60 ) >> 5 ) {
 case 1 : str = "Full rate support only MS/fullrate speech version 1 supported" ;
 break ;
 case 2 : str = "Dual rate support MS/half rate speech version 1 preferred, full rate speech version 1 also supported" ;
 break ;
 case 3 : str = "Dual rate support MS/full rate speech version 1 preferred, half rate speech version 1 also supported" ;
 break ;
 default : str = "Reserved" ;
 break ;
 }
 }
 break ;
 default : switch ( ( oct & 0x60 ) >> 5 ) {
 case 1 : str = "Full rate support only MS" ;
 break ;
 case 2 : str = "Dual rate support MS/half rate preferred" ;
 break ;
 case 3 : str = "Dual rate support MS/full rate preferred" ;
 break ;
 default : str = "Reserved" ;
 break ;
 }
 break ;
 }
 break ;
 default : str = "(dissect problem)" ;
 break ;
 }
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_radio_channel_requirement , tvb , curr_offset , 1 , oct , "%s" , str ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_bearer_cap_coding_standard , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_transfer_mode , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_itc , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( add_string ) g_snprintf ( add_string , string_len , " - (%s)" , str ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 switch ( itc ) {
 case DE_BC_ITC_SPEECH : subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , - 1 , ett_bc_oct_3a , & item , "Octets 3a - Speech Versions" ) ;
 saved_offset = curr_offset ;
 do {
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_coding , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_bits_item ( subtree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_speech_vers_ind , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 }
 while ( extended && ( ( len - ( curr_offset - offset ) ) > 0 ) ) ;
 proto_item_set_len ( item , curr_offset - saved_offset ) ;
 break ;
 default : subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_4 , NULL , "Octet 4" ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , is_uplink ? hf_gsm_a_dtap_compression_up : hf_gsm_a_dtap_compression , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_structure , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_duplex_mode , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_configuration , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_nirr , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_establishment , tvb , curr_offset , 1 , ENC_NA ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_5 , NULL , "Octet 5" ) ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_access_identity , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_rate_adaption , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_signalling_access_protocol , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 if ( ! extended ) goto bc_octet_6 ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_5a , NULL , "Octet 5a" ) ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_other_itc , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_other_rate_adaption , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 5 , 3 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 if ( ! extended ) goto bc_octet_6 ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_5b , NULL , "Octet 5b" ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_rate_adaption_header , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_multiple_frame_establishment_support , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_mode_of_operation , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_logical_link_identifier_negotiation , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_assignor_assignee , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_in_out_band , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 7 , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 bc_octet_6 : subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_6 , NULL , "Octet 6" ) ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_layer_1_identity , tvb , curr_offset , 1 , oct , "%s" , ( ( oct & 0x60 ) == 0x20 ) ? "Octet identifier" : "Reserved" ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_user_information_layer_1_protocol , tvb , curr_offset , 1 , oct , "%s" , ( oct & 0x1e ) ? "Reserved" : "Default layer 1 protocol" ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_synchronous , tvb , curr_offset , 1 , ENC_NA ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 if ( ! extended ) goto bc_octet_7 ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_6a , NULL , "Octet 6a" ) ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_number_of_stop_bits , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_negotiation , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_number_of_data_bits , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_user_rate , tvb , curr_offset , 1 , oct , "%s" , val_to_str_const ( oct & 0xF , gsm_a_dtap_user_rate_vals , "Reserved" ) ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 if ( ! extended ) goto bc_octet_7 ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_6b , NULL , "Octet 6b" ) ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_v110_x30_rate_adaptation , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_nic_on_tx , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_nic_on_rx , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_parity_information , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 if ( ! extended ) goto bc_octet_7 ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_6c , NULL , "Octet 6c" ) ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_connection_element , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_modem_type , tvb , curr_offset , 1 , oct , "%s" , val_to_str_const ( oct & 0x1f , gsm_a_dtap_modem_type_vals , "Reserved" ) ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 if ( ! extended ) goto bc_octet_7 ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_6d , NULL , "Octet 6d" ) ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_other_modem_type , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_fixed_network_user_rate , tvb , curr_offset , 1 , oct , "%s" , val_to_str_const ( oct & 0x1f , gsm_a_dtap_fixed_network_user_rate_vals , "Reserved" ) ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 if ( ! extended ) goto bc_octet_7 ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_6e , NULL , "Octet 6e" ) ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( is_uplink == IS_UPLINK_TRUE ) {
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_acceptable_channel_codings_TCH_F14_4 , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_acceptable_channel_codings_spare20 , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_acceptable_channel_codings_TCH_F9_6 , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_acceptable_channel_codings_TCH_F4_8 , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_maximum_number_of_traffic_channels , tvb , curr_offset , 1 , ( oct & 0x07 ) + 1 , "%u TCH" , ( oct & 0x07 ) + 1 ) ;
 }
 else {
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_acceptable_channel_codings_spare78 , tvb , curr_offset , 1 , oct , "Spare" ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_maximum_number_of_traffic_channels , tvb , curr_offset , 1 , oct , "Spare" ) ;
 }
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 if ( ! extended ) goto bc_octet_7 ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_6f , NULL , "Octet 6f" ) ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 extended = ( oct & 0x80 ) ? FALSE : TRUE ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_uimi , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( is_uplink == IS_UPLINK_TRUE ) {
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_wanted_air_interface_user_rate , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 else {
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_wanted_air_interface_user_rate , tvb , curr_offset , 1 , oct , "Spare" ) ;
 }
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 if ( ! extended ) goto bc_octet_7 ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_6g , NULL , "Octet 6g" ) ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( is_uplink == IS_UPLINK_TRUE ) {
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_acceptable_channel_codings_ext_TCH_F28_8 , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_acceptable_channel_codings_ext_TCH_F32_0 , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_acceptable_channel_codings_ext_TCH_F43_2 , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_channel_coding_asymmetry_indication , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 else {
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_edge_channel_codings , tvb , curr_offset , 1 , oct , "Spare" ) ;
 }
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 6 , 2 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 NO_MORE_DATA_CHECK ( len ) ;
 bc_octet_7 : subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_bc_oct_7 , NULL , "Octet 7" ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_layer_2_identity , tvb , curr_offset , 1 , oct , "%s" , ( ( oct & 0x60 ) == 0x40 ) ? "Octet identifier" : "Reserved" ) ;
 proto_tree_add_uint_format_value ( subtree , hf_gsm_a_dtap_user_information_layer_2_protocol , tvb , curr_offset , 1 , oct , "%s" , val_to_str_const ( oct & 0x1F , gsm_a_dtap_user_info_layer2_vals , "Reserved" ) ) ;
 break ;
 }
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }