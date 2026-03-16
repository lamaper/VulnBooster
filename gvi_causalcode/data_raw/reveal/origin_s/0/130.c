static int dissect_rsl_ie_rlm_cause ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_item * ti ;
 proto_tree * ie_tree ;
 guint length ;
 guint8 ie_id ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_RLM_CAUSE ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_rlm_cause , & ti , "RLM Cause IE " ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 length = tvb_get_guint8 ( tvb , offset ) ;
 proto_item_set_len ( ti , length + 2 ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( tree , hf_rsl_extension_bit , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_cause , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 return offset ;
 }