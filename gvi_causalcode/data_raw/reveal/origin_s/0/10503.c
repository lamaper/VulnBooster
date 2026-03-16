void dissect_q931_high_layer_compat_ie ( tvbuff_t * tvb , int offset , int len , proto_tree * tree ) {
 guint8 octet ;
 guint8 coding_standard ;
 guint8 pres_method ;
 guint8 characteristics ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 coding_standard = octet & 0x60 ;
 pres_method = octet & 0x03 ;
 proto_tree_add_item ( tree , hf_q931_extension_ind , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint ( tree , hf_q931_coding_standard , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_interpretation , tvb , offset , 1 , octet ) ;
 proto_tree_add_uint ( tree , hf_q931_pres_meth_prot_prof , tvb , offset , 1 , octet ) ;
 offset += 1 ;
 len -= 1 ;
 if ( ( coding_standard != Q931_ITU_STANDARDIZED_CODING ) || ( pres_method != Q931_HIGH_LAYER_PROTOCOL_PROFILE ) ) {
 proto_tree_add_item ( tree , hf_q931_high_layer_compat_data , tvb , offset , len , ENC_NA ) ;
 return ;
 }
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 characteristics = octet & 0x7F ;
 proto_tree_add_item ( tree , hf_q931_extension_ind , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint ( tree , hf_q931_high_layer_characteristics , tvb , offset , 1 , octet ) ;
 offset += 1 ;
 len -= 1 ;
 if ( ! ( octet & Q931_IE_VL_EXTENSION ) ) {
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( ( characteristics == Q931_AUDIOVISUAL ) || ( characteristics == 0x61 ) || ( characteristics == 0x62 ) || ( characteristics == 0x68 ) ) {
 proto_tree_add_item ( tree , hf_q931_extension_ind , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint ( tree , hf_q931_extended_audiovisual_characteristics , tvb , offset , 1 , octet ) ;
 }
 else if ( ( characteristics == Q931_MANAGEMENT ) || ( characteristics == Q931_MAINTENANCE ) ) {
 proto_tree_add_item ( tree , hf_q931_extension_ind , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint ( tree , hf_q931_extended_high_layer_characteristics , tvb , offset , 1 , octet ) ;
 }
 }
 }