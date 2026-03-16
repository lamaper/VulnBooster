static int dissect_rsl_ie_L3_inf ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset , gboolean is_mandatory , l3_inf_t type ) {
 proto_item * ti ;
 proto_tree * ie_tree ;
 tvbuff_t * next_tvb ;
 guint16 length ;
 guint8 ie_id ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_L3_INF ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_L3_inf , & ti , "L3 Information IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 length = tvb_get_ntohs ( tvb , offset ) ;
 proto_item_set_len ( ti , length + 3 ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_length , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset = offset + 2 ;
 if ( type == L3_INF_CCCH ) {
 proto_tree_add_item ( ie_tree , hf_rsl_llsdu_ccch , tvb , offset , length , ENC_NA ) ;
 next_tvb = tvb_new_subset_length ( tvb , offset , length ) ;
 call_dissector ( gsm_a_ccch_handle , next_tvb , pinfo , top_tree ) ;
 }
 else if ( type == L3_INF_SACCH ) {
 proto_tree_add_item ( ie_tree , hf_rsl_llsdu_sacch , tvb , offset , length , ENC_NA ) ;
 next_tvb = tvb_new_subset_length ( tvb , offset , length ) ;
 call_dissector ( gsm_a_sacch_handle , next_tvb , pinfo , top_tree ) ;
 }
 else {
 proto_tree_add_item ( ie_tree , hf_rsl_llsdu , tvb , offset , length , ENC_NA ) ;
 next_tvb = tvb_new_subset_length ( tvb , offset , length ) ;
 call_dissector ( gsm_a_dtap_handle , next_tvb , pinfo , top_tree ) ;
 }
 offset = offset + length ;
 return offset ;
 }