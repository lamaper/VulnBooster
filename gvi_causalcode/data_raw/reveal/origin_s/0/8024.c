static void dissect_q931_ns_facilities_ie ( tvbuff_t * tvb , int offset , int len , proto_tree * tree ) {
 guint8 octet ;
 int netid_len ;
 if ( len == 0 ) return ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 netid_len = octet & 0x7F ;
 proto_tree_add_item ( tree , hf_q931_netid_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 if ( netid_len != 0 ) {
 if ( len == 0 ) return ;
 proto_tree_add_item ( tree , hf_q931_netid_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_q931_netid_plan , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 netid_len -- ;
 if ( len == 0 ) return ;
 if ( netid_len > len ) netid_len = len ;
 if ( netid_len != 0 ) {
 proto_tree_add_item ( tree , hf_q931_netid , tvb , offset , netid_len , ENC_NA | ENC_ASCII ) ;
 offset += netid_len ;
 len -= netid_len ;
 }
 }
 if ( len == 0 ) return ;
 proto_tree_add_item ( tree , hf_q931_netid_facility_specification , tvb , offset , len , ENC_NA ) ;
 }