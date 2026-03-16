static void dissect_q931_channel_identification_ie ( tvbuff_t * tvb , int offset , int len , proto_tree * tree ) {
 guint8 octet ;
 guint8 coding_standard ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_q931_extension_ind , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_channel_interface_explicit , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_channel_interface_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_channel_exclusive , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_channel_dchan , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( octet & Q931_NOT_BASIC_CHANNEL ) {
 proto_tree_add_item ( tree , hf_q931_channel_selection_pri , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 else {
 proto_tree_add_item ( tree , hf_q931_channel_selection_bri , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 }
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_INTERFACE_IDENTIFIED ) {
 guint8 octet2 ;
 guint32 identifier_val = 0 ;
 int identifier_offset = offset ;
 int identifier_len = 0 ;
 do {
 if ( len == 0 ) break ;
 octet2 = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 len -= 1 ;
 identifier_len ++ ;
 identifier_val <<= 7 ;
 identifier_val |= octet2 & 0x7F ;
 }
 while ( ! ( octet2 & Q931_IE_VL_EXTENSION ) ) ;
 if ( identifier_len != 0 ) {
 proto_tree_add_uint ( tree , hf_q931_channel_interface_id , tvb , identifier_offset , identifier_len , identifier_val ) ;
 }
 }
 if ( octet & Q931_NOT_BASIC_CHANNEL ) {
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 coding_standard = octet & 0x60 ;
 proto_tree_add_item ( tree , hf_q931_extension_ind , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint ( tree , hf_q931_coding_standard , tvb , offset , 1 , octet ) ;
 if ( coding_standard != Q931_ITU_STANDARDIZED_CODING ) {
 proto_tree_add_item ( tree , hf_q931_channel_data , tvb , offset , len , ENC_NA ) ;
 return ;
 }
 proto_tree_add_item ( tree , hf_q931_channel_map , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_channel_element_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 if ( octet & Q931_IS_SLOT_MAP ) {
 while ( len ) {
 proto_tree_add_item ( tree , hf_q931_channel_slot_map , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 }
 }
 else {
 guint8 octet2 ;
 do {
 if ( len == 0 ) break ;
 octet2 = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_q931_extension_ind , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_channel_number , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 }
 while ( ! ( octet2 & Q931_IE_VL_EXTENSION ) ) ;
 }
 }
 }