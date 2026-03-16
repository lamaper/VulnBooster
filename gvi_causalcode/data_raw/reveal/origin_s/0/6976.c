static guint16 de_gcc_call_ref ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guint32 value ;
 curr_offset = offset ;
 value = tvb_get_ntohl ( tvb , curr_offset ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_gcc_call_ref , tvb , curr_offset , 4 , ENC_BIG_ENDIAN ) ;
 if ( value & 0x10 ) {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_gcc_call_ref_has_priority , tvb , curr_offset , 4 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_gcc_call_priority , tvb , curr_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_gcc_spare_1 , tvb , curr_offset , 4 , ENC_NA ) ;
 }
 else {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_gcc_call_ref_has_priority , tvb , curr_offset , 4 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_gcc_spare_4 , tvb , curr_offset , 4 , ENC_NA ) ;
 }
 curr_offset += 4 ;
 return ( curr_offset - offset ) ;
 }