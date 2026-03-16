void dissect_q931_bearer_capability_ie ( tvbuff_t * tvb , int offset , int len , proto_tree * tree ) {
 guint8 octet ;
 guint8 coding_standard ;
 guint8 it_rate ;
 guint8 uil2_protocol ;
 guint8 uil3_protocol ;
 guint8 add_l3_info ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 coding_standard = octet & 0x60 ;
 if ( coding_standard != Q931_ITU_STANDARDIZED_CODING ) {
 proto_tree_add_item ( tree , hf_q931_bearer_capability_data , tvb , offset , len , ENC_NA ) ;
 proto_tree_add_boolean ( tree , hf_q931_extension_ind , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_coding_standard , tvb , offset , 1 , octet ) ;
 return ;
 }
 proto_tree_add_boolean ( tree , hf_q931_extension_ind , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_coding_standard , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_information_transfer_capability , tvb , offset , 1 , octet ) ;
 offset += 1 ;
 len -= 1 ;
 if ( ! ( octet & Q931_IE_VL_EXTENSION ) ) {
 if ( len == 0 ) return ;
 proto_tree_add_item ( tree , hf_q931_out_band_negotiation , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 len -= 1 ;
 }
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_boolean ( tree , hf_q931_extension_ind , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_transfer_mode , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_information_transfer_rate , tvb , offset , 1 , octet ) ;
 it_rate = octet & 0x1F ;
 offset += 1 ;
 len -= 1 ;
 if ( it_rate == Q931_IT_RATE_MULTIRATE ) {
 if ( len == 0 ) return ;
 proto_tree_add_item ( tree , hf_q931_bearer_capability_rate_multiplier , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 }
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( ( octet & 0x60 ) == 0x20 ) {
 proto_tree_add_boolean ( tree , hf_q931_extension_ind , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_layer_ident , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_uil1 , tvb , offset , 1 , octet ) ;
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l1_done ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_q931_layer_1 , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_layer_1_in_band_negotiation , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_bearer_capability_user_rate , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l1_done ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_q931_bearer_capability_intermediate_rate , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_send_data_net_independent_clock , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_accept_data_net_independent_clock , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_send_data_flow_control , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_accept_data_flow_control , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l1_done ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_q931_rate_adaption_header , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_multiple_frame_establishment , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_mode_of_operation , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_protocol_negotiation , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_message_originator , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_negotiation_is_done , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l1_done ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_q931_bearer_capability_stop_bits , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_bearer_capability_data_bits , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_bearer_capability_parity , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l1_done ;
 proto_tree_add_item ( tree , hf_q931_bearer_capability_duplex , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_q931_bearer_capability_modem_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 }
 l1_done : ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( ( octet & 0x60 ) == 0x40 ) {
 proto_tree_add_boolean ( tree , hf_q931_extension_ind , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_layer_ident , tvb , offset , 1 , octet ) ;
 uil2_protocol = octet & 0x1F ;
 proto_tree_add_item ( tree , hf_q931_uil2 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l2_done ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( uil2_protocol == Q931_UIL2_USER_SPEC ) {
 proto_tree_add_item ( tree , hf_q931_uil2_info , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 else {
 proto_tree_add_item ( tree , hf_q931_bearer_capability_mode , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l2_done ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) & 0x7F ;
 proto_tree_add_uint_format_value ( tree , hf_q931_bearer_capability_window_size , tvb , offset , 1 , octet , "octet & 0x7F%u k" , octet ) ;
 offset += 1 ;
 len -= 1 ;
 }
 l2_done : ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( ( octet & 0x60 ) == 0x60 ) {
 proto_tree_add_boolean ( tree , hf_q931_extension_ind , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_layer_ident , tvb , offset , 1 , octet ) ;
 uil3_protocol = octet & 0x1F ;
 proto_tree_add_item ( tree , hf_q931_uil3 , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l3_done ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 switch ( uil3_protocol ) {
 case Q931_UIL3_X25_PL : case Q931_UIL3_ISO_8208 : case Q931_UIL3_X223 : proto_tree_add_item ( tree , hf_q931_bearer_capability_mode , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l3_done ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_q931_bearer_capability_default_packet_size , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l3_done ;
 if ( len == 0 ) return ;
 proto_tree_add_item ( tree , hf_q931_bearer_capability_packet_window_size , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 case Q931_UIL3_USER_SPEC : proto_tree_add_uint_format_value ( tree , hf_q931_bearer_capability_default_packet_size , tvb , offset , 1 , 1 << ( octet & 0x0F ) , "%u octets" , 1 << ( octet & 0x0F ) ) ;
 break ;
 case Q931_UIL3_TR_9577 : add_l3_info = ( octet & 0x0F ) << 4 ;
 if ( octet & Q931_IE_VL_EXTENSION ) goto l3_done ;
 if ( len < 2 ) return ;
 octet = tvb_get_guint8 ( tvb , offset + 1 ) ;
 add_l3_info |= ( octet & 0x0F ) ;
 proto_tree_add_uint ( tree , hf_q931_uil3_additional , tvb , offset , 2 , add_l3_info ) ;
 break ;
 }
 }
 l3_done : ;
 }