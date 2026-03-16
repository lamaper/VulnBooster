static int dissect_rsl_ie_full_imm_ass_inf ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_item * ti ;
 proto_tree * ie_tree ;
 guint length ;
 tvbuff_t * next_tvb ;
 guint8 ie_id ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_FULL_IMM_ASS_INF ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_full_imm_ass_inf , & ti , "Full Immediate Assign Info IE " ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 length = tvb_get_guint8 ( tvb , offset ) ;
 proto_item_set_len ( ti , length + 2 ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_length , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( ie_tree , hf_rsl_full_immediate_assign_info_field , tvb , offset , length , ENC_NA ) ;
 next_tvb = tvb_new_subset_length ( tvb , offset , length ) ;
 call_dissector ( gsm_a_ccch_handle , next_tvb , pinfo , top_tree ) ;
 offset = offset + length ;
 return offset ;
 }