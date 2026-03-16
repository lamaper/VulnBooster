void dissect_q931_progress_indicator_ie ( tvbuff_t * tvb , int offset , int len , proto_tree * tree ) {
 guint8 octet ;
 guint8 coding_standard ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 coding_standard = octet & 0x60 ;
 proto_tree_add_uint ( tree , hf_q931_coding_standard , tvb , offset , 1 , octet ) ;
 if ( coding_standard != Q931_ITU_STANDARDIZED_CODING ) {
 proto_tree_add_item ( tree , hf_q931_progress_indicator_data , tvb , offset , len , ENC_NA ) ;
 return ;
 }
 proto_tree_add_item ( tree , hf_q931_progress_indicator_location , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 if ( len == 0 ) return ;
 proto_tree_add_item ( tree , hf_q931_progress_indicator_description , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 }